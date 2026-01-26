// Fill out your copyright notice in the Description page of Project Settings.


#include "System/ProjectBasicAGameState.h"

void AProjectBasicAGameState::BeginPlay()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectBasicAGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AProjectBasicAGameState::Tick(float DeltaTime)
{
}
