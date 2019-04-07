// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBuildingsManager.h"
#include "Interfaces/ResourceBuilding.h"
#include "Engine/World.h"
#include "Player/States/DefaultPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Structs/ResourceDeposit.h"

void UResourceBuildingsManager::GatherResources()
{
	const auto PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ADefaultPlayerState>();
	check(PlayerState);
	for (const auto& Building : ResourceBuildings)
	{
		const auto Resource = Building->GetProducingResource();
		// TODO: gather resources and place in in player's storage
	}
}

void UResourceBuildingsManager::AddResourceBuilding(TScriptInterface<IResourceBuilding> Building)
{
	check(Building);
	ResourceBuildings.Add(Building);
}
