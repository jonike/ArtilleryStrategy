// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Task.generated.h"

class IAgent;
/**
 * 
 */
UCLASS(BlueprintType)
class UTILITYAI_API UTask : public UObject
{
	GENERATED_BODY()

public:
	virtual void Run(TScriptInterface<IAgent> Agent);
};
