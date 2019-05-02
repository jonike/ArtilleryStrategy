// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"
#include "Interfaces/WorldTile.h"
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

void ABaseResourceBuilding::PostPlaced(const TScriptInterface<IWorldTile> Tile)
{
	Super::PostPlaced(Tile);
	PopulateProducedResourcesContainer(Tile);
	const auto TurnProcessor = GetTurnProcessor(this);
	// TODO: bind ReceiveOnTurnEnded and ReceiveOnTurnStarted automatically (maybe through method BindToTurnStart/BindToTurnEnd)
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ABaseResourceBuilding::ReceiveOnTurnEnded);
}

void ABaseResourceBuilding::PopulateProducedResourcesContainer(const TScriptInterface<IWorldTile> Tile)
{
	if (Tile->HasResourceDeposits())
	{
		const auto& ResourcesOnTile = Tile->GetResourceDeposits();
		for (const auto& Resource : ResourcesOnTile)
		{
			if (ResourcesCanProduce.Contains(Resource.ResourceAmount.ResourceHandle))
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
