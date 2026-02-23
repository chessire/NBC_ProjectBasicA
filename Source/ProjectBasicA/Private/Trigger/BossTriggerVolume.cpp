// Fill out your copyright notice in the Description page of Project Settings.


#include "Trigger/BossTriggerVolume.h"


// Sets default values
ABossTriggerVolume::ABossTriggerVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABossTriggerVolume::BeginPlay()
{
	Super::BeginPlay();
}

void ABossTriggerVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bInitializedBoss == false)
	{
		// generate boss
		bInitializedBoss = true;
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red,
			FString::Printf(TEXT("[ABossTriggerVolume] Gerate Boss"))
		);
	}
}

void ABossTriggerVolume::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (bInitializedBoss)
	{
		// Boss AI Process
	}
}

