// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Objects/AttackTargets.h"
#include "Objects/ExpansionPreferences.h"
#include "AI/Controllers/AdvancedAIController.h"
#include "EnemiesLibrary.generated.h"

class AAIController;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UEnemiesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UAttackTargets* GetAttackTargets(const AAIController* Controller);

	static UExpansionPreferences* GetExpansionPreferences(const AAIController* Controller);

private:
	static AAdvancedAIController* GetAdvancedController(AAIController* Controller);
	static const AAdvancedAIController* GetAdvancedController(const AAIController* Controller);
};
