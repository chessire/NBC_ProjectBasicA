// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/BasicAnimInstance.h"

void UBasicAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	if (BeginMontage)
	{
		Montage_Play(
			BeginMontage,
			1.f,
			EMontagePlayReturnType::MontageLength,
			0.f,
			true
		);
	}
	
	PawnOwner = TryGetPawnOwner();
}

void UBasicAnimInstance::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBasicAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(PawnOwner.IsValid() == false)
		return;

	FRotator BaseAimRotator = PawnOwner->GetBaseAimRotation();
	FRotator ActorRotator = PawnOwner->GetActorRotation();
	FRotator DeltaRotator = BaseAimRotator - ActorRotator;

	DeltaRotator.Normalize();

	Roll = DeltaRotator.Roll;
	Pitch = DeltaRotator.Pitch;
	Yaw = DeltaRotator.Yaw;
}
