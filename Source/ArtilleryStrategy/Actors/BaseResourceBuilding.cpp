// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Components/TurnProcessorComponent.h"

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
	const auto TurnProcessor = GetTurnProcessor(this);
	// TODO: bind ReceiveOnTurnEnded and ReceiveOnTurnStarted automatically (maybe through method BindToTurnStart/BindToTurnEnd)
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ABaseResourceBuilding::ReceiveOnTurnEnded);
}

void ABaseResourceBuilding::ReceiveOnTurnEnded()
{
	Super::ReceiveOnTurnEnded();
}
