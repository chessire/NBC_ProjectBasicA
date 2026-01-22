// Copyright Epic Games, Inc. All Rights Reserved.

#include "System/ProjectBasicAGameMode.h"
#include "System/ProjectBasicAPlayerController.h"
#include "System/ProjectBasicAGameState.h"
#include "System/ProjectBasicAPlayerState.h"
#include "System/ProjectBasicAHUD.h"
#include "System/ProjectAGameInstance.h"
#include "Pawn/ProjectBasicACharacter.h"

AProjectBasicAGameMode::AProjectBasicAGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectBasicAPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
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

void AProjectBasicAGameMode::BeginPlay()
{
	Super::BeginPlay();
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

void AProjectBasicAGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AProjectBasicAGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
