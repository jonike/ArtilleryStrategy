// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WorldTile.h"
#include "OwnerState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOwnerState : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API IOwnerState
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TArray<TScriptInterface<IWorldTile>> GetOwnedTiles() const = 0;
	virtual TArray<TScriptInterface<IBuilding>> GetOwnedBuildings() const = 0;

	virtual void RegisterBuyingCell(TScriptInterface<IWorldTile> Tile) = 0;
	virtual void RegisterBuyingBuilding(TScriptInterface<IBuilding> Building) = 0;
};
