// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Brains/Brain.h"
#include "RepeatingBrain.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, EditInlineNew)
class UTILITYAI_API URepeatingBrain : public UBrain
{
	GENERATED_BODY()

public:
	void Initialize(TScriptInterface<IAgent> Instigator) override;

	UFUNCTION(BlueprintCallable)
	virtual void Stop();

protected:
	void BeginDestroy() override;

private:
	UPROPERTY(EditAnywhere)
	float Step = 0.2f;

	FTimerHandle Timer;
};
