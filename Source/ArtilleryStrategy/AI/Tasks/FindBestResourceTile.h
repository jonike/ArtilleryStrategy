// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindBestResourceTile.generated.h"

/**
 * \brief Task for finding best tile with resources
 */
UCLASS()
class ARTILLERYSTRATEGY_API UFindBestResourceTile : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindBestResourceTile();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector ResultKey;
};
