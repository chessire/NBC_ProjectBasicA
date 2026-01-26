// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectBasicAGameMode.generated.h"

// TODO_GEUKMIN EXAM : TSharedPtr, TSharedRef 예시
USTRUCT()
struct FHelloWorld
{
	GENERATED_BODY()

	FHelloWorld() : Hello(0) {}
	FHelloWorld(int InHello) : Hello(InHello) {}
	int Hello;
};
// TODO_GEUKMIN EXAM : TSharedPtr, TSharedRef 예시 end

class APawn;
class APlayerController;
class AGameState;
class APlayerState;
class AHUD;

UCLASS(minimalapi)
class AProjectBasicAGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectBasicAGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<APawn> PlayerPawnBPClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerController> PlayerControllerBPClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGameState> GameStateBPClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<APlayerState> PlayerStateBPClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AHUD> HudBPClass;

	TWeakObjectPtr<APawn> Pawn;
	TSoftObjectPtr<APawn> PawnB;

	TSharedPtr<FHelloWorld> HelloPtr;
	TSharedPtr<FHelloWorld> HelloPtrShareable;
};



