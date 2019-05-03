// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnLimitNotReached.h"
#include "Libraries/ASLibrary.h"
#include "AIController.h"

bool UTurnLimitNotReached::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto PlayerTurnLimits = UASLibrary::GetPlayerTurnLimitsForController(OwnerComp.GetAIOwner());
	switch (Type)
	{
		case ELimitType::Buildings:
			return !PlayerTurnLimits.GetBuildingsLimit().IsLimitReached();
		case ELimitType::Tiles: 
			return !PlayerTurnLimits.GetTilesLimit().IsLimitReached();
		default:
			checkNoEntry();
			return false;
	}
}

void UTurnLimitNotReached::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UTurnLimitNotReached::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
}
