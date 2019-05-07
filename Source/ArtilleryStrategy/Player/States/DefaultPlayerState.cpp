// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"
#include "Objects/ResourceStorage.h"
#include "Objects/ResourceBuildingsManager.h"
#include "Components/TurnProcessorComponent.h"
#include "Player/Controllers/DefaultPlayerController.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	Storage = CreateDefaultSubobject<UResourceStorage>(TEXT("Resource storage"));
	ResourceBuildingsManager = CreateDefaultSubobject<UResourceBuildingsManager>(TEXT("Resource buildings manager"));
}

void ADefaultPlayerState::ReceiveOnTurnStarted()
{
	TurnLimits.ResetAllLimits();
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
	OwnedBuildings.Emplace(Building);
}

void ADefaultPlayerState::RegisterBuyingCell(const TScriptInterface<IWorldTile> Tile)
{
	TurnLimits.GetTilesLimit().Increment();
	OwnedTiles.Emplace(Tile);
}

TArray<TScriptInterface<IWorldTile>> ADefaultPlayerState::GetOwnedTiles() const
{
	return OwnedTiles;
}

TArray<TScriptInterface<IBuilding>> ADefaultPlayerState::GetOwnedBuildings() const
{
	return OwnedBuildings;
}
