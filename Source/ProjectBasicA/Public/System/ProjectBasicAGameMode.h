// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
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
class AProjectBasicAGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AProjectBasicAGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void StartPlay() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// TODO_GEUKMIN EXAM : 잘못 사용된 UniquePtr 예시
	//TUniquePtr<FHelloWorld>& GetUnique() { return HelloUnique; }
	//TUniquePtr<FHelloWorld>* GetUnique() { return HelloUnique; }
	// TODO_GEUKMIN EXAM : 잘못 사용된 UniquePtr 예시 end
	
	// TODO_GEUKMIN EXAM : 좋은 UniquePtr 예시
	TUniquePtr<FHelloWorld>&& ReciveUnique()
	{
		if(HelloUnique.IsValid() == false)
			return nullptr;

		return MoveTemp(HelloUnique);
	}
	// TODO_GEUKMIN EXAM : 좋은 UniquePtr 예시 end

	// TODO_GEUKMIN EXAM : TUniquePtr 예시
	// 첫번째 인자는 RValue로 가져다 쓴다.
	// 두번째 인자는 참조자로 가져다 쓴다.
	// 세번째 인자는 포인터 변수에 주소값을 가져와 쓴다.
	void HandleUnique1(TUniquePtr<FHelloWorld> InUniquePtr)
	{
		UE_LOG(LogTemp, Error, TEXT("HelloWorld %d"), InUniquePtr->Hello);
	}
	void HandleUnique2(TUniquePtr<FHelloWorld>&& InUniquePtr, TUniquePtr<FHelloWorld>& InUniquePtr2, TUniquePtr<FHelloWorld>* InUniquePtr3)
	{
		UE_LOG(LogTemp, Error, TEXT("HelloWorld %d"), InUniquePtr->Hello);
	}
	void HandleUnique3(TUniquePtr<FHelloWorld>&& InUniquePtr)
	{
		// TUniquePtr<FHelloWorld>로만 받아오면 원본이 소멸될 수 있음
		if(Pawn == nullptr)
			return;

		HelloUnique2 = MoveTemp(InUniquePtr);
	}
	// TODO_GEUKMIN EXAM : TUniquePtr 예시 end

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

	TUniquePtr<FHelloWorld> HelloUnique;
	TUniquePtr<FHelloWorld> HelloUnique2;
};



