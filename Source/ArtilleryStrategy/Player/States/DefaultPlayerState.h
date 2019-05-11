// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/PlayerRepository.h"
#include "Structs/PlayerTurnLimits.h"
#include "Interfaces/TurnDependent.h"
#include "Interfaces/OwnerState.h"
#include "Interfaces/PlayerProperty.h"
#include "DefaultPlayerState.generated.h"

class IWorldTile;
class IBuilding;
class UResourceBuildingsManager;
class UResourceStorage;
/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerState : public APlayerState, public IPlayerRepository, public ITurnDependent, public IOwnerState
{
	GENERATED_BODY()

public:
	ADefaultPlayerState();

	UFUNCTION(Category = "Wallet", BlueprintPure)
	UResourceStorage* GetResourceWallet() const override { return Storage; }

	UFUNCTION()
	void RegisterBuyingBuilding(TScriptInterface<IBuilding> Building) override;

	UFUNCTION()
	void RegisterBuyingCell(TScriptInterface<IWorldTile> Tile) override;

	const TSet<UObject*>& GetOwnedTiles() const override;
	const TSet<UObject*>& GetOwnedBuildings() const override;

	bool CanBuyTile(TScriptInterface<IPlayerProperty> Tile) const override;
	bool CanBuyBuilding(TScriptInterface<IPlayerProperty> Building) const override;

	void ReceiveOnTurnStarted() override;

	FPlayerTurnLimits& GetTurnLimits();
	const FPlayerTurnLimits& GetTurnLimits() const;

	UResourceBuildingsManager* GetResourceBuildingsManager() const;

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

	UPROPERTY(VisibleInstanceOnly)
	TSet<UObject*> OwnedTiles;

	UPROPERTY(VisibleInstanceOnly)
	TSet<UObject*> OwnedBuildings;
};
