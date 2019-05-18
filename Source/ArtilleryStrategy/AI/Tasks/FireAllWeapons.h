// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FireAllWeapons.generated.h"

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
};