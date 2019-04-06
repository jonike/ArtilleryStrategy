// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtilleryStrategyGMB.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Player/HUD/DefaultHUD.h"
#include "Game/States/DefaultGS.h"
#include "Components/TurnProcessorComponent.h"

AArtilleryStrategyGMB::AArtilleryStrategyGMB()
{
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();
	HUDClass = ADefaultHUD::StaticClass();
	GameStateClass = ADefaultGS::StaticClass();
	TurnProcessorComponent = CreateDefaultSubobject<UTurnProcessorComponent>(TEXT("Turn processor component"));
}
