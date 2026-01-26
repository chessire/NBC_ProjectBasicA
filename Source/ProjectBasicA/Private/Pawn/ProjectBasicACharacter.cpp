// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawn/ProjectBasicACharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"

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

void AProjectBasicACharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	// TODO_GEUKMIN EXAM : IsNull
	if(CameraBoom.IsNull()) // if(CameraBoom == nullptr)
		return;
	// TODO_GEUKMIN EXAM : IsNull End
}

TObjectPtr<class USpringArmComponent> AProjectBasicACharacter::GetCameraBoom() const
{
	if (CameraBoom.IsA<USpringArmComponent>())
		return Cast<USpringArmComponent>(CameraBoom);

	return nullptr;
}
