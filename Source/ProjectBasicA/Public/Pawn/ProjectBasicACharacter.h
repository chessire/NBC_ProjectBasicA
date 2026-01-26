// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectBasicACharacter.generated.h"

UCLASS(Blueprintable)
class AProjectBasicACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProjectBasicACharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	//FORCEINLINE TObjectPtr<class UCameraComponent> GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE TObjectPtr<class USpringArmComponent> GetCameraBoom() const;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> CameraBoom;
};


// TODO_GEUKMIN DESC : RTTI에 대한 설명
//enum class EItemType
//{
//	Healing,
//	Mana,
//};
//
//class Item
//{
//public:
//	virtual EItemType GetType() = 0;
//};
//
//class HealingPotion : public Item
//{
//public:
//	virtual EItemType GetType() override { return EItemType::Healing; }
//
//	void Heal() {}
//};
//
//class ManaPotion : public Item
//{
//public:
//	virtual EItemType GetType() override { return EItemType::Mana; }
//};
//
//// upcasting
//Item* item = new ManaPotion(); // 문제 없음
//
//// downcasting
//HealingPotion* healing = (HealingPotion*)item;
//
//// crash~
//healing->Heal();

// dynamic_cast : 다운캐스팅 실패시 nullptr, 다운캐스팅 성공시 올바른 값
// ?
// dynamic_cast 쓰면 되겠네~
// RTTI라는 어마무시한 친구를 건드립니다.
// RunTime Type Identifier
// 어마무시하게 느려집니다.
// 
// TODO_GEUKMIN DESC : RTTI에 대한 설명 End