// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindCapitalTile.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UFindCapitalTile : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindCapitalTile();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector CapitalTileKey;
};
