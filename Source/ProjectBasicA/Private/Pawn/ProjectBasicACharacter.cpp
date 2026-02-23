// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawn/ProjectBasicACharacter.h"

#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY(LogBasicACharacter);

AProjectBasicACharacter::AProjectBasicACharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	// TODO_GEUKMIN EXAM : IsA
	if (CameraBoom.IsA<USpringArmComponent>())
	{
		auto* CameraBoomInst = Cast<USpringArmComponent>(CameraBoom);
		CameraBoomInst->TargetArmLength = 800.f;
		CameraBoomInst->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	}
	// TODO_GEUKMIN EXAM : IsA End

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AProjectBasicACharacter::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow,
		FString::Printf(TEXT("[AProjectBasicACharacter::BeginPlay]"))
	);
}

void AProjectBasicACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(CommonMoveAction, ETriggerEvent::Triggered, this, &AProjectBasicACharacter::OnCommonMove);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AProjectBasicACharacter::OnAttack);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &AProjectBasicACharacter::OnDashTriggered);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AProjectBasicACharacter::OnDashCanceled);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Canceled, this, &AProjectBasicACharacter::OnDashCanceled);
	}
	else
	{
		UE_LOG(LogBasicACharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectBasicACharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// GetWorld()->LineTraceSingle
	// GetWorld()->SweepSingle
	// DrawDebugLine()
	// DrawDebugCircle()
}

TObjectPtr<class USpringArmComponent> AProjectBasicACharacter::GetCameraBoom() const
{
	if (CameraBoom.IsA<USpringArmComponent>())
		return Cast<USpringArmComponent>(CameraBoom);

	return nullptr;
}

void AProjectBasicACharacter::OnCommonMove(const FInputActionValue& value)
{
	FVector2D Axis = value.Get<FVector2D>();
	FVector InputVector(Axis.X, Axis.Y, 0.f);
	InputVector.Normalize();
	if (bDashMode)
	{
		const FVector& ActorLocation = GetActorLocation();
		const FQuat& ActorQuat = GetActorQuat();
		FVector SweepTraceEnd = ActorLocation + InputVector * DashDistance;
		const FCollisionShape& Shape = GetCapsuleComponent()->GetCollisionShape();
		FHitResult Hit;
		if (GetWorld()->SweepSingleByChannel(
			Hit,
			ActorLocation,
			SweepTraceEnd,
			ActorQuat,
			ECC_Visibility,
			Shape
		))
		{
			DrawDebugSphere(GetWorld(), Hit.Location, 20.f, 16, FColor::Red);
			bDashMode = false;
		}
	}
	else
	{
		GetMovementComponent()->AddInputVector(
			InputVector * Speed
		);
	}
}

FVector AProjectBasicACharacter::GetFireFrontVector() {
	FQuat Quat = GetMesh()->GetSocketQuaternion(TEXT("fire_point_socket"));
	float x = Quat.X;
	float y = Quat.Y;
	float z = Quat.Z;
	float w = Quat.W;

	float vx = 2 * (x * z + w * y);
	float vy = 2 * (y * z - w * x);
	float vz = 1 - 2 * (x * x + y * y);

	return FVector(vx, vy, vz);
}

void AProjectBasicACharacter::OnAttack()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC == nullptr)
		return;
		
	float MouseX, MouseY;
	if (PC->GetMousePosition(MouseX, MouseY) == false)
		return;
	
	FHitResult HitResult;
	if (PC->GetHitResultUnderCursor(ECC_GameTraceChannel2, false, HitResult) == false)
		return;
	
	FVector CursorHitLocation = HitResult.Location;
	DrawDebugCircle(GetWorld(), CursorHitLocation, 16.f, 16, FColor::Green);
	
	FVector FirePoint = GetMesh()->GetSocketLocation(TEXT("fire_point_socket"));
	FVector FireNorm = CursorHitLocation - FirePoint;
	FireNorm.Normalize();
	FVector FireEndPoint = FirePoint + FireNorm * FireDistance;
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		FirePoint,
		FireEndPoint,
		ECC_Visibility
	))
	{
		DrawDebugLine(GetWorld(), FirePoint, Hit.Location, FColor(0, 255, 0));	
	}
}

void AProjectBasicACharacter::OnDashTriggered()
{
	bDashMode = true;

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(DashTimerHandle, FTimerDelegate::CreateLambda([this]()
	{
		bDashMode = false;
	}), 0.2f, false);
}

void AProjectBasicACharacter::OnDashCanceled()
{
	bDashMode = false;
}
