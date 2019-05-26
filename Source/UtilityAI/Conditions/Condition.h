// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Condition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class UTILITYAI_API UCondition : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool Evaluate() const;

protected:
	UFUNCTION(BlueprintCallable)
	virtual bool EvaluateRaw() const;

private:
	UPROPERTY(EditAnywhere)
	bool bInvert = false;
};
