// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/GridPlatform.h"

ADefaultAIController::ADefaultAIController()
{
	bWantsPlayerState = true;
}

UMaterialInterface* ADefaultAIController::GetOwnerMaterial() const
{
	return OwnerMaterial;
}

UTexture2D* ADefaultAIController::GetOwnerIcon() const
{
	return OwnerIcon;
}

TScriptInterface<IWallet> ADefaultAIController::GetWallet() const
{
	return GetPlayerState<ADefaultPlayerState>();
}

void ADefaultAIController::BuyCell(TScriptInterface<ICanBeOwned> Cell)
{
	// TODO: copy pasted from player controller
	const auto State = GetPlayerState<ADefaultPlayerState>();
	check(State);
	if (State->GetTurnLimits().GetTilesLimit().IsLimitReached())
	{
		return;
	}

	if (TryToBuyWithPack(Cell->GetResourcesToOwn()))
	{
		Cell->SetOwnerController(this);
		// OnTileBought.Broadcast(Cell.GetObject());
		State->RegisterBuyingCell(Cell.GetObject());
	}
}

void ADefaultAIController::CreateSelectedBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass)
{
	// TODO: copy pasted from player controller
	const auto State = GetPlayerState<ADefaultPlayerState>();
	check(State);
	if (State->GetTurnLimits().GetBuildingsLimit().IsLimitReached())
	{
		return;
	}

	if (TryToBuyDefaultBuilding(BuildingClass))
	{
		const auto Building = Cell->CreateBuilding(BuildingClass);
		// OnBuildingCreated.Broadcast(Building);
		State->RegisterBuyingBuilding(Building);
	}
}

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();	
	UseBlackboard(BlackboardData, Blackboard);
	RunBehaviorTree(TurnBehavior);
}

bool ADefaultAIController::TryToBuyWithPack(const FResourcePack& ResourcePack) const
{
	// TODO: copy pasted from player controller
	const auto Wallet = GetWallet();
	if (Wallet)
	{
		const auto ResourceWallet = Wallet->GetResourceWallet();
		check(ResourceWallet);
		if (ResourceWallet->IsEnoughPack(ResourcePack))
		{
			ResourceWallet->SpendResourcePack(ResourcePack);
			return true;
		}
	}
	return false;
}

bool ADefaultAIController::TryToBuyDefaultBuilding(const TSubclassOf<AActor> BuildingClass) const
{
	// TODO: copy pasted from player controller
	const auto DefaultBuildingObject = Cast<ICanBeOwned>(BuildingClass.GetDefaultObject());
	check(DefaultBuildingObject);
	return TryToBuyWithPack(DefaultBuildingObject->GetResourcesToOwn());
}
