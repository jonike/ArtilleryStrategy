// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BuySelectedTile.generated.h"

/**
 * \brief Task for buying previously selected tile
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuySelectedTile : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBuySelectedTile();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SelectedTile;

	UPROPERTY(EditAnywhere)
	bool bShouldClearSelectedTile = true;

	EBTNodeResult::Type BuySelected(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UObject* ObjectToBuy) const;
};
