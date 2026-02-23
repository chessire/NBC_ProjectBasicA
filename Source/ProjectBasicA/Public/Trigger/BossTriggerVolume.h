// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "BossTriggerVolume.generated.h"

UCLASS()
class PROJECTBASICA_API ABossTriggerVolume : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABossTriggerVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
private:
	bool bInitializedBoss = false;
};
