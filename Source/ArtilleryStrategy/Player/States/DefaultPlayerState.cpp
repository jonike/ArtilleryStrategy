// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"
#include "Objects/ResourceStorage.h"
#include "Objects/ResourceBuildingsManager.h"
#include "Components/TurnProcessorComponent.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Interfaces/WorldTile.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	Storage = CreateDefaultSubobject<UResourceStorage>(TEXT("Resource storage"));
	ResourceBuildingsManager = CreateDefaultSubobject<UResourceBuildingsManager>(TEXT("Resource buildings manager"));
}

void ADefaultPlayerState::ReceiveOnTurnStarted()
{
	TurnLimits.ResetAllLimits();
}

FPlayerTurnLimits& ADefaultPlayerState::GetTurnLimits()
{
	return TurnLimits;
}

const FPlayerTurnLimits& ADefaultPlayerState::GetTurnLimits() const
{
	return TurnLimits;
}

UResourceBuildingsManager* ADefaultPlayerState::GetResourceBuildingsManager() const
{
	return ResourceBuildingsManager;
}

void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();
	const auto TurnProcessor = GetTurnProcessor(this);
	TurnProcessor->OnTurnStarted.AddDynamic(this, &ADefaultPlayerState::ReceiveOnTurnStarted);
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ADefaultPlayerState::ReceiveOnTurnEnded);
}

void ADefaultPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADefaultPlayerState::RegisterBuyingBuilding(const TScriptInterface<IBuilding> Building)
{
	TurnLimits.GetBuildingsLimit().Increment();
	OwnedBuildings.Emplace(Building.GetObject());
}

void ADefaultPlayerState::RegisterBuyingCell(const TScriptInterface<IWorldTile> Tile)
{
	TurnLimits.GetTilesLimit().Increment();
	OwnedTiles.Emplace(Tile.GetObject());
}

TSet<UObject*> ADefaultPlayerState::GetOwnedTiles() const
{
	return OwnedTiles;
}

TSet<UObject*> ADefaultPlayerState::GetOwnedBuildings() const
{
	return OwnedBuildings;
}

bool ADefaultPlayerState::CanBuyTile(const TScriptInterface<IPlayerProperty> Tile) const
{
	return !GetTurnLimits().GetTilesLimit().IsLimitReached()
			&& GetResourceWallet()->IsEnoughPack(Tile->GetResourcesToOwn());
}

bool ADefaultPlayerState::CanBuyBuilding(const TScriptInterface<IPlayerProperty> Building) const
{
	return !GetTurnLimits().GetBuildingsLimit().IsLimitReached()
			&& GetResourceWallet()->IsEnoughPack(Building->GetResourcesToOwn());
}
