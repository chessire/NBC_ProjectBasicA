// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AttackAnimNotify.h"

#pragma optimize("", off)
void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp->GetOwner() == nullptr)
		return;

	// AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner());
	// if (MyCharacter == nullptr)
	// 	return;
	//
	// MyCharacter->Attack(); // 이 함수 안에서 충돌처리
	
	FString Name = MeshComp->GetOwner()->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow,
		FString::Printf(TEXT("[AttackAnimNotify] %s"), *Name)
	);
}
#pragma optimize("", on)
