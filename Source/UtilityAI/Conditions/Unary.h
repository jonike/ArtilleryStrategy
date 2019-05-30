// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conditions/Condition.h"
#include "Unary.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UUnary : public UCondition
{
	GENERATED_BODY()

protected:
	virtual bool EvaluateOne(bool Result) const;

	bool EvaluateRaw() const override final;

private:
	UPROPERTY(EditAnywhere, Instanced)
	UCondition* Condition;
};
