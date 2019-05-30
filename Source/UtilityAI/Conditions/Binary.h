// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conditions/Condition.h"
#include "Binary.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UBinary : public UCondition
{
	GENERATED_BODY()

protected:
	virtual bool EvaluateTwo(bool FirstResult, bool SecondResult) const;

	bool EvaluateRaw() const override final;

private:
	UPROPERTY(EditAnywhere, Instanced)
	UCondition* First;

	UPROPERTY(EditAnywhere, Instanced)
	UCondition* Second;
};
