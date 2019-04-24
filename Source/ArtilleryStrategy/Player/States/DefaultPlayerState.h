// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Wallet.h"
#include "Structs/PlayerTurnLimits.h"
#include "Interfaces/TurnDependent.h"
#include "DefaultPlayerState.generated.h"

class IGridPlatform;
class IBuilding;
class UResourceBuildingsManager;
class UResourceStorage;
/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerState : public APlayerState, public IWallet, public ITurnDependent
{
	GENERATED_BODY()

public:
	ADefaultPlayerState();

	UFUNCTION(Category = "Wallet", BlueprintPure)
	UResourceStorage* GetResourceWallet() const override { return Storage; }

	void ReceiveOnTurnStarted() override;

	auto& GetTurnLimits() { return TurnLimits; }

	auto GetResourceBuildingsManager() const { return ResourceBuildingsManager; }

protected:
	void BeginPlay() override;
	void PostInitializeComponents() override;

private:
	UPROPERTY(Category = "Resources", EditAnywhere)
	UResourceStorage* Storage;

	UPROPERTY(Category = "Resources", VisibleInstanceOnly)
	UResourceBuildingsManager* ResourceBuildingsManager;

	UPROPERTY(Category="Turn limits", EditAnywhere)
	FPlayerTurnLimits TurnLimits;

	UFUNCTION()
	void ReceiveOnBuildingCreated(TScriptInterface<IBuilding> Building);

	UFUNCTION()
	void ReceiveOnTileBought(TScriptInterface<IGridPlatform> Tile);
};
