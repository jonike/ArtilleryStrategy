// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Components/TurnProcessorComponent.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"

bool ABaseResourceBuilding::IsProducingResource() const
{
	return ProducedResources.Num() > 0;
}

void ABaseResourceBuilding::AddResourceDeposit(FResourceDeposit& Deposit)
{
	ProducedResources.Add(Deposit);
}

TSet<FResourceDeposit>& ABaseResourceBuilding::GetProducingResources()
{
	return ProducedResources;
}

void ABaseResourceBuilding::PostPlaced(const TScriptInterface<IGridPlatform> Tile)
{
	Super::PostPlaced(Tile);
	PopulateProducedResourcesContainer(Tile);
	const auto TurnProcessor = GetTurnProcessor(this);
	// TODO: bind ReceiveOnTurnEnded and ReceiveOnTurnStarted automatically (maybe through method BindToTurnStart/BindToTurnEnd)
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ABaseResourceBuilding::ReceiveOnTurnEnded);
}

void ABaseResourceBuilding::PopulateProducedResourcesContainer(const TScriptInterface<IGridPlatform> Tile)
{
	if (Tile->HasResourceDeposit())
	{
		// TODO: rename method (gets resource depositS)
		const auto& ResourcesOnTile = Tile->GetResourceDeposit();
		// TODO: rewrite check whether the building can produce resource on the tile (tip: use FDataTableRowHandle)
		for (const auto& Resource : ResourcesOnTile)
		{
			if (ResourcesCanProduce.ContainsByPredicate([&Resource](const auto & Row) { return Row.RowName == Resource.ResourceAmount.Resource.FriendlyName; }))
			{
				ProducedResources.Add(Resource);
			}
		}
	}
}

void ABaseResourceBuilding::ReceiveOnTurnEnded()
{
	Super::ReceiveOnTurnEnded();
	const auto Controller = GetWorld()->GetFirstPlayerController<IOwnerController>();
	if (Controller)
	{
		const auto Wallet = Controller->GetWallet();
		check(Wallet);
		const auto ResourceWallet = Wallet->GetResourceWallet();
		check(ResourceWallet);
		for (const auto& Resource : ProducedResources)
		{
			ResourceWallet->AddResource(Resource.ResourceAmount);
		}
	}
}
