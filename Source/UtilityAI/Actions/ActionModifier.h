// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Conditions/Condition.h"
#include "ActionModifier.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct UTILITYAI_API FActionModifier
{
	GENERATED_BODY()

public:
	float GetCurrentValue() const;

private:
	UPROPERTY(EditAnywhere)
	float SuccessValue = 0.f;

	UPROPERTY(EditAnywhere)
	float FailureValue = 0.0f;

	UPROPERTY(EditAnywhere, Instanced)
	UCondition* Condition = nullptr;

	bool EvaluateConditionTree() const;
};
