// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Agents/Agent.h"
#include "AgentLibrary.generated.h"

class UBrain;
/**
 * 
 */
UCLASS()
class UTILITYAI_API UAgentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TScriptInterface<IAgent> GetAgent(const UBrain* Brain);
};
