// Copyright Epic Games, Inc. All Rights Reserved.

#include "System/ProjectBasicAGameMode.h"
#include "System/ProjectBasicAPlayerController.h"
#include "System/ProjectBasicAGameState.h"
#include "System/ProjectBasicAPlayerState.h"
#include "System/ProjectBasicAHUD.h"
#include "System/ProjectAGameInstance.h"
#include "Pawn/ProjectBasicACharacter.h"

void UHelloWorld1::FunctionA()
{
	UE_LOG(LogTemp, Error, TEXT("Hello FunctionA"));
}

void UHelloWorld1::FunctionB()
{
}

void UHelloWorld1::FunctionC()
{
}


AProjectBasicAGameMode::AProjectBasicAGameMode()
{
	// set default pawn class to our Blueprinted character
	APawn::StaticClass();
	static ConstructorHelpers::FClassFinder<APawn> FindPlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (FindPlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = FindPlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> FindPlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(FindPlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = FindPlayerControllerBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AGameState> FindGameStateBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownGameState"));
	if(FindGameStateBPClass.Class != nullptr)
	{
		GameStateClass = FindGameStateBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerState> FindPlayerStateBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerState"));
	if(FindPlayerStateBPClass.Class != nullptr)
	{
		PlayerStateClass = FindPlayerStateBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AHUD> FindHudBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownHUD"));
	if(FindHudBPClass.Class != nullptr)
	{
		HUDClass = FindHudBPClass.Class;
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AProjectBasicAGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	if (PlayerPawnBPClass != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass;
	}

	// set default controller to our Blueprinted controller
	if(PlayerControllerBPClass != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass;
	}

	if(GameStateBPClass != nullptr)
	{
		GameStateClass = GameStateBPClass;
	}

	if(PlayerStateBPClass != nullptr)
	{
		PlayerStateClass = PlayerStateBPClass;
	}

	if(HudBPClass != nullptr)
	{
		HUDClass = HudBPClass;
	}

	if (auto* GI = Cast<UProjectAGameInstance>(GetGameInstance()))
	{
		// todo using gi
	}
}

void AProjectBasicAGameMode::StartPlay()
{
	Super::StartPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
		return;

	FunctionA();

	Pawn = PlayerController->GetPawn();
	// TODO_GEUKMIN EXAM : MakeShared, MakeShareable, MakeUnique 예시
	HelloPtr = MakeShared<FHelloWorld>(100);
	HelloPtrShareable = MakeShareable<FHelloWorld>(new FHelloWorld(100));
	HelloUnique = MakeUnique<FHelloWorld>(1000);
	// TODO_GEUKMIN EXAM : MakeShared, MakeShareable, MakeUnique 예시 end

	// TODO_GEUKMIN EXAM : TUniquePtr 예시
	//MoveTemp(HelloUnique);
	//TUniquePtr<FHelloWorld>&& InUniquePtr = MoveTemp(HelloUnique);
	//TUniquePtr<FHelloWorld> InUniquePtr2 = MoveTemp(HelloUnique);

	HandleUnique1(MoveTemp(HelloUnique));
	HandleUnique2(MoveTemp(HelloUnique), HelloUnique, &HelloUnique);
	// TODO_GEUKMIN EXAM : TUniquePtr 예시 End
}

void AProjectBasicAGameMode::BeginPlay()
{
	Super::BeginPlay();
}

// TODO_GEUKMIN EXAM : TSharedRef 예시
void InitHelloWorld(TSharedRef<FHelloWorld> A)
{
	A->Hello = 100;
}
// TODO_GEUKMIN EXAM : TSharedRef 예시 end

// TODO_GEUKMIN EXAM : TWeakPtr 예시
void UseHelloWorld(TWeakPtr<FHelloWorld> A)
{
	//if(A.IsValid() == false) // IsValid가 false일 때, pin할 경우 nullptr
	//	return;

	TSharedPtr<FHelloWorld> PinnedA = A.Pin();
	if(PinnedA == nullptr && PinnedA->Hello > 0)
		PinnedA->Hello -= 1;
}
// TODO_GEUKMIN EXAM : TWeakPtr 예시 end

void AProjectBasicAGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO_GEUKMIN EXAM : IsValid 예시
	// TODO_GEUKMIN DESC : Dangling 설명
	// 1. PlayerController에 Pawn이 있음
	// 2. GameModeBase에서 Pawn을 PlayerController로부터 가져옴
	// 3. PlayerController에서 Pawn을 지움
	// 4. GameModeBase의 Pawn은 nullptr가 아님
	// 5. 우리는 이걸 Dangling 이라고 표현하기로 했어요~
	if (Pawn.IsValid() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("Removed Pawn."));
	}
	// TODO_GEUKMIN DESC : Dangling 설명 end
	// TODO_GEUKMIN EXAM : IsValid 예시 end

	// TODO_GEUKMIN EXAM : TSharedPtr, TSharedRef 예시
	TSharedRef<FHelloWorld> HelloRef = HelloPtr.ToSharedRef();
	TSharedPtr<FHelloWorld> HelloPtr2 = HelloRef.ToSharedPtr();

	if(HelloPtr != nullptr)
		InitHelloWorld(HelloPtr.ToSharedRef());
	// TODO_GEUKMIN EXAM : TSharedPtr, TSharedRef 예시 end
}

void AProjectBasicAGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AProjectBasicAGameMode::FunctionA()
{
	UObject* Object = this;
	UFunction* StartPlayFunction = Object->StaticClass()->FindFunctionByName(TEXT("FunctionA"));
	if (StartPlayFunction->IsNative())
	{
		FFrame Stack(Object, StartPlayFunction, nullptr, nullptr, StartPlayFunction->ChildProperties);

		HelloWorld = NewObject<UHelloWorld1>(this);
		UObject* Ptr = HelloWorld;
		UClass* HelloWorldClass = HelloWorld->GetClass();
		UFunction* Function = HelloWorldClass->FindFunctionByName(TEXT("FunctionA"));
		Function->Invoke(Ptr, Stack, nullptr);
	}
}

void AProjectBasicAGameMode::FunctionB()
{
}

void AProjectBasicAGameMode::FunctionC()
{
}
