// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FireAllWeapons.generated.h"

class UCurveFloat;
class IWeaponBuilding;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UFireAllWeapons : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFireAllWeapons();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetKey;

	UPROPERTY(EditAnywhere)
	UCurveFloat* AngleCurve;

	void RotateWeapon(TScriptInterface<IWeaponBuilding> Weapon, const FVector& Target) const;
	void FireWeapon(TScriptInterface<IWeaponBuilding> Weapon) const;

	/** Return plane angle and horizon angle (in that exact order) for weapon for shooting */
	TPair<float, float> GetWeaponAngles(TScriptInterface<IWeaponBuilding> Weapon, const FVector& Target) const;

	FVector UnpackTarget(UBehaviorTreeComponent& OwnerComp) const;
};
