// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBASICA_API UAttackAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	// 에디터에서 노티파이 선택 시 보이는 이름(선택)
	virtual FString GetNotifyName_Implementation() const override { return TEXT("Attack"); }

	// 핵심: 이 프레임에 호출됨
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowPrivateAccess=true))
	float KnockbackPower = 1.0f;

};
