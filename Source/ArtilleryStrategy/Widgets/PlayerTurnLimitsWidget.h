// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TurnDependent.h"
#include "Structs/ValueLimit.h"
#include "Interfaces/WorldTile.h"
#include "PlayerTurnLimitsWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UPlayerTurnLimitsWidget : public UUserWidget, public ITurnDependent
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void FillTilesLimit(const FValueLimit& Limit);

	UFUNCTION(BlueprintImplementableEvent)
	void FillBuildingsLimit(const FValueLimit& Limit);

	UFUNCTION()
	void ReceiveOnTileBought(TScriptInterface<IGridPlatform> Tile);

	UFUNCTION()
	void ReceiveOnBuildingCreated(TScriptInterface<IBuilding> Tile);

	void NativeConstruct() override;
	void ReceiveOnTurnStarted() override;

private:
	// TODO: avoid storing copies of player limits
	FValueLimit TilesLimit;
	FValueLimit BuildingsLimit;

	void ResetLimits();
};
