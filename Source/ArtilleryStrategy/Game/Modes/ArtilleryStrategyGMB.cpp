// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Player/HUD/DefaultHUD.h"
#include "Components/CapitalPlacementGenerator.h"
#include "Game/States/DefaultGS.h"

AArtilleryStrategyGMB::AArtilleryStrategyGMB()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	CapitalPlacementGenerator = CreateDefaultSubobject<UCapitalPlacementGenerator>(TEXT("Capital placement generator"));

	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();
	HUDClass = ADefaultHUD::StaticClass();
	GameStateClass = ADefaultGS::StaticClass();
}

void AArtilleryStrategyGMB::BeginPlay()
{
	check(GridGenerator);
	GridGenerator->GenerateGrid();
	CapitalPlacementGenerator->PlaceCapitalsForAll();
}
