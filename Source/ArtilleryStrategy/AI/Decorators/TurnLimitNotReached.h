// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "TurnLimitNotReached.generated.h"

UENUM()
enum class ELimitType
{
	Buildings,
	Tiles,
};

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UTurnLimitNotReached : public UBTDecorator
{
	GENERATED_BODY()

public:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;
	void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	ELimitType Type;
};
