// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindBestTileForResourceBuilding.generated.h"

struct FWorldParams;

/**
 * \brief Task for finding best acquired tile with resources to build a resource production building on it
 */
UCLASS()
class ARTILLERYSTRATEGY_API UFindBestTileForResourceBuilding : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindBestTileForResourceBuilding();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ResultTile;

	EBTNodeResult::Type GetBestResourceTile(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const FWorldParams& Params);
};
