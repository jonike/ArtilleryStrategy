// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemiesLibrary.h"

UAttackTargets* UEnemiesLibrary::GetAttackTargets(const AAIController* Controller)
{
	if (const auto AdvController = GetAdvancedController(Controller))
	{
		return AdvController->GetAttackTargets();
	}
	return nullptr;
}

UExpansionPreferences* UEnemiesLibrary::GetExpansionPreferences(const AAIController* Controller)
{
	if (const auto AdvController = GetAdvancedController(Controller))
	{
		return AdvController->GetExpansionPreferences();
	}
	return nullptr;
}

AAdvancedAIController* UEnemiesLibrary::GetAdvancedController(AAIController* Controller)
{
	return Cast<AAdvancedAIController>(Controller);
}

const AAdvancedAIController* UEnemiesLibrary::GetAdvancedController(const AAIController* Controller)
{
	return Cast<AAdvancedAIController>(Controller);
}
