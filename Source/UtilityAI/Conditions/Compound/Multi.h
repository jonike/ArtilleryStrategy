// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Conditions/Condition.h"
#include "Multi.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UMulti : public UCondition
{
	GENERATED_BODY()

protected:
	virtual bool ProcessValuePair(bool Current, bool NextValue) const;
	virtual bool GetInitialValue() const;

	bool EvaluateRaw() const override final;

private:
	UPROPERTY(EditAnywhere, Instanced)
	TArray<UCondition*> Conditions;
};
