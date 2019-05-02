// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "CanBuyBuildings.generated.h"

class IBuilding;
class IGridPlatform;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanBuyBuildings : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Represents class that can buy buildings for itself
 */
class ARTILLERYSTRATEGY_API ICanBuyBuildings
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * \brief Creates building of given class on the tile
	 * \param Cell place where to create building
	 * \param BuildingClass building class to spawn
	 */
	virtual void CreateSelectedBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) = 0;
};
