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
	const auto OwnerController = GetWorld()->GetFirstPlayerController<IOwnerController>();
	if (OwnerController)
	{
		const auto Wallet = OwnerController->GetWallet();
		check(Wallet);
		const auto ResourceWallet = Wallet->GetResourceWallet();
		check(ResourceWallet);
		for (const auto& Resource : ProducedResources)
		{
			ResourceWallet->AddResource(Resource.ResourceAmount);
		}
	}
}
