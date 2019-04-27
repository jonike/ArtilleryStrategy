// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BuySelected.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ARTILLERYSTRATEGY_API UBuySelected : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBuySelected();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	virtual EBTNodeResult::Type BuySelected(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UObject* ObjectToBuy);

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector Selected;
};
