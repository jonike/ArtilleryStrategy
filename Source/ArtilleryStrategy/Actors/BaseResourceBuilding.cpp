// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Objects/ResourceBuildingsManager.h"

bool ABaseResourceBuilding::IsProducingResource() const
{
	return ProducedResource != nullptr;
}

void ABaseResourceBuilding::AddResourceDeposit(UResourceDeposit* Deposit)
{
	ProducedResource = Deposit;
}

UResourceDeposit* ABaseResourceBuilding::GetProducingResource() const
{
	return ProducedResource;
}

void ABaseResourceBuilding::PostPlaced(const TScriptInterface<IGridPlatform> Tile)
{
	Super::PostPlaced(Tile);
	if (Tile->HasResourceDeposit())
	{
		ProducedResource = Tile->GetResourceDeposit();
		const auto PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ADefaultPlayerState>();
		if (PlayerState)
		{
			PlayerState->GetResourceBuildingsManager()->AddResourceBuilding(this);
		}
	}
}
