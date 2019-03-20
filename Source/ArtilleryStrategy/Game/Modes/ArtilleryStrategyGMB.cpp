// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Player/HUD/DefaultHUD.h"

AArtilleryStrategyGMB::AArtilleryStrategyGMB()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();
	HUDClass = ADefaultHUD::StaticClass();
}

void AArtilleryStrategyGMB::BeginPlay()
{
	check(GridGenerator);

	GridGenerator->GenerateGrid();
}
