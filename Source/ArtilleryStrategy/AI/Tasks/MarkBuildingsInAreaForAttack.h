// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MarkBuildingsInAreaForAttack.generated.h"

class UAttackTargets;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UMarkBuildingsInAreaForAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMarkBuildingsInAreaForAttack();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CenterTileKey;

	UPROPERTY(EditAnywhere)
	int Radius = 6;

	UAttackTargets* GetAttackTargets(UBehaviorTreeComponent& OwnerComp) const;
};
