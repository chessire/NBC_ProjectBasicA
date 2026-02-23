// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ProjectBasicACharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBasicACharacter, Log, All);

UCLASS(Blueprintable)
class AProjectBasicACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AProjectBasicACharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	//FORCEINLINE TObjectPtr<class UCameraComponent> GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE TObjectPtr<class USpringArmComponent> GetCameraBoom() const;

protected:
	virtual void OnCommonMove(const struct FInputActionValue& value);
	virtual void OnAttack();
	virtual void OnDashTriggered();
	virtual void OnDashCanceled();
	FVector GetFireFrontVector();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> CameraBoom;

	
	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* CommonMoveAction;
	
	/** Attack Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* AttackAction;
	
	/** Dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess = "true"))
	float FireDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(AllowPrivateAccess = "true"))
	float DashDistance;

	bool bDashMode;
	FTimerHandle DashTimerHandle;
};


// TODO_GEUKMIN DESC : RTTI�� ���� ����
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
//Item* item = new ManaPotion(); // ���� ����
//
//// downcasting
//HealingPotion* healing = (HealingPotion*)item;
//
//// crash~
//healing->Heal();

// dynamic_cast : �ٿ�ĳ���� ���н� nullptr, �ٿ�ĳ���� ������ �ùٸ� ��
// ?
// dynamic_cast ���� �ǰڳ�~
// RTTI��� ������� ģ���� �ǵ帳�ϴ�.
// RunTime Type Identifier
// ������ϰ� �������ϴ�.
// 
// TODO_GEUKMIN DESC : RTTI�� ���� ���� End
