// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionModifier.h"
#include "Action.generated.h"

/**
 *
 */
UCLASS(BlueprintType, EditInlineNew)
class UTILITYAI_API UAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	float Evaluate() const;

private:
	UPROPERTY(EditAnywhere)
	TArray<FActionModifier> Modifiers;

	float EvaluateRaw() const;
};
