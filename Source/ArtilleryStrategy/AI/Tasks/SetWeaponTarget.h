// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Objects/AttackTargets.h"
#include "SetWeaponTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API USetWeaponTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USetWeaponTarget();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(Category="Input", EditAnywhere)
	FBlackboardKeySelector WeaponKey;

	UPROPERTY(Category="Output", EditAnywhere)
	FBlackboardKeySelector TargetKey;

	// TODO: add interface "CanBeTargeted" for result type 
	AActor* SelectTarget(const UBehaviorTreeComponent& OwnerComp, UAttackTargets* Targets) const;
};
