// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "CanBuyTiles.generated.h"

class IWorldTile;
class IPlayerProperty;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanBuyTiles : public UInterface
{
	GENERATED_BODY()
};

/**
 *	\brief Represents class that can buy tiles for itself
 */
class ARTILLERYSTRATEGY_API ICanBuyTiles
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BuyTile(TScriptInterface<IPlayerProperty> Tile) = 0;
};
