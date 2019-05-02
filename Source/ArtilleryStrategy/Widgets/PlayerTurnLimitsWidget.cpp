// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTurnLimitsWidget.h"
#include "Components/TurnProcessorComponent.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Player/States/DefaultPlayerState.h"

void UPlayerTurnLimitsWidget::ReceiveOnTileBought(TScriptInterface<IWorldTile> Tile)
{
	TilesLimit.Increment();
	FillTilesLimit(TilesLimit);
}

void UPlayerTurnLimitsWidget::ReceiveOnBuildingCreated(TScriptInterface<IBuilding> Tile)
{
	BuildingsLimit.Increment();
	FillBuildingsLimit(BuildingsLimit);
}

void UPlayerTurnLimitsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const auto TurnProcessor = GetTurnProcessor(this);
	TurnProcessor->OnTurnStarted.AddDynamic(this, &UPlayerTurnLimitsWidget::ReceiveOnTurnStarted);

	// TODO: a lot of coupling (needs both player controller and player state)
	const auto PlayerController = GetWorld()->GetFirstPlayerController<ADefaultPlayerController>();
	check(PlayerController);
	PlayerController->OnTileBought.AddDynamic(this, &UPlayerTurnLimitsWidget::ReceiveOnTileBought);
	PlayerController->OnBuildingCreated.AddDynamic(this, &UPlayerTurnLimitsWidget::ReceiveOnBuildingCreated);

	const auto PlayerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<ADefaultPlayerState>();
	check(PlayerState);
	TilesLimit = PlayerState->GetTurnLimits().GetTilesLimit();
	BuildingsLimit = PlayerState->GetTurnLimits().GetBuildingsLimit();
	FillTilesLimit(TilesLimit);
	FillBuildingsLimit(BuildingsLimit);
}

void UPlayerTurnLimitsWidget::ReceiveOnTurnStarted()
{
	ResetLimits();
}

void UPlayerTurnLimitsWidget::ResetLimits()
{
	BuildingsLimit.Reset();
	TilesLimit.Reset();
	FillTilesLimit(TilesLimit);
	FillBuildingsLimit(BuildingsLimit);
}
