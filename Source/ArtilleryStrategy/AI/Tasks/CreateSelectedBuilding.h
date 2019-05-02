// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CreateSelectedBuilding.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UCreateSelectedBuilding : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCreateSelectedBuilding();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TileKey;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector BuildingClassKey;

	UPROPERTY(EditAnywhere)
	bool bShouldClearTileKey = true;

	UPROPERTY(EditAnywhere)
	bool bShouldClearBuildingClassKey = true;
};
