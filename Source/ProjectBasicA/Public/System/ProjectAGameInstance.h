// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBASICA_API UProjectAGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void OnStart() override;
	virtual void Shutdown() override;
};
