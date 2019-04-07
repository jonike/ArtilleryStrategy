// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "Interfaces/GridPlatform.h"

bool ABaseResourceBuilding::IsProducingResource() const
{
	return ProducedResources.Num() > 0;
}

void ABaseResourceBuilding::AddResourceDeposit(FResourceDeposit& Deposit)
{
	ProducedResources.Add(Deposit);
}

TArray<FResourceDeposit>& ABaseResourceBuilding::GetProducingResource()
{
	return ProducedResources;
}

void ABaseResourceBuilding::PostPlaced(const TScriptInterface<IGridPlatform> Tile)
{
	Super::PostPlaced(Tile);
	if (Tile->HasResourceDeposit())
	{
		ProducedResources = Tile->GetResourceDeposit();
	}
}
