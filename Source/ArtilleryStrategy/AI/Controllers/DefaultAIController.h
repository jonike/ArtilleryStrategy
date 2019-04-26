// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Behavior", EditAnywhere)
	UBehaviorTree* TurnBehavior;

	UPROPERTY(Category = "Behavior", EditAnywhere)
	UBlackboardData* BlackboardData;
};
