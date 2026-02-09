// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AttackAnimNotifyState.h"

void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp->GetOwner() == nullptr)
		return;
	
	FString Name = MeshComp->GetOwner()->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow,
		FString::Printf(TEXT("[AttackAnimNotifyState] Begin %s (%f)"), *Name, TotalDuration)
	);
}

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (MeshComp->GetOwner() == nullptr)
		return;

	// AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());
	// if (MyCharacter == nullptr)
	// 	return;
	//
	// MyCharacter->Attack(); // 이 함수 안에서 충돌처리
	
	FString Name = MeshComp->GetOwner()->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow,
		FString::Printf(TEXT("[AttackAnimNotifyState] Tick %s (%f)"), *Name, FrameDeltaTime)
	);
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp->GetOwner() == nullptr)
		return;
	
	FString Name = MeshComp->GetOwner()->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow,
		FString::Printf(TEXT("[AttackAnimNotifyState] End %s"), *Name)
	);
}
