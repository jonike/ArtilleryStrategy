// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBuildingsManager.h"
#include "Interfaces/ResourceBuilding.h"
#include "Engine/World.h"
#include "Player/States/DefaultPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Objects/ResourceDeposit.h"

void UResourceBuildingsManager::GatherResources()
{
	const auto PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ADefaultPlayerState>();
	check(PlayerState);
	for (const auto& Building : ResourceBuildings)
	{
		const auto Resource = Building->GetProducingResource();
		PlayerState->GetResourceWallet()->Add(Resource);
	}
}

void UResourceBuildingsManager::AddResourceBuilding(TScriptInterface<IResourceBuilding> Building)
{
	check(Building);
	ResourceBuildings.Add(Building);
}