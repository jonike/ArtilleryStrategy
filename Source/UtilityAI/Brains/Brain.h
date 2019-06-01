// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Brain.generated.h"

class IAgent;
class UAction;
/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class UTILITYAI_API UBrain : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Initialize(TScriptInterface<IAgent> Instigator);

	UFUNCTION(BlueprintCallable)
	virtual void Run() const;

protected:
	UFUNCTION(BlueprintCallable)
	virtual UAction* SelectAction() const;

	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IAgent> GetAgent() const;

	UFUNCTION(BlueprintCallable)
	const TArray<UAction*>& GetActions() const;

	UFUNCTION(BlueprintCallable)
	float GetAutoSelectThreshold() const;

private:
	UPROPERTY(EditAnywhere)
	TArray<UAction*> Actions;

	UPROPERTY(EditAnywhere)
	float AutoSelectThreshold = 0.9f;

	UPROPERTY()
	TScriptInterface<IAgent> Agent;
};
