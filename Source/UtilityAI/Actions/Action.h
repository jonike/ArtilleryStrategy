// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionModifier.h"
#include "Action.generated.h"

class UTask;
class IAgent;
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

	UFUNCTION(BlueprintCallable)
	virtual void Run(TScriptInterface<IAgent> Agent);

private:
	UPROPERTY(EditAnywhere)
	TArray<FActionModifier> Modifiers;

	UPROPERTY(EditAnywhere)
	TArray<UTask*> Tasks;

	float EvaluateRaw() const;
};
