// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Building.generated.h"

class IGridPlatform;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuilding : public UInterface
{
	GENERATED_BODY()
};

/**
 *	\brief Represents building
 */
class ARTILLERYSTRATEGY_API IBuilding
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * \brief Actions before building was placed on the tile
	 * \param Tile where building was placed
	 */
	virtual void PrePlaced(TScriptInterface<IGridPlatform> Tile) = 0;

	/**
	 * \brief Actions after the building was placed
	 * \param Tile where building was placed
	 */
	virtual void PostPlaced(TScriptInterface<IGridPlatform> Tile) = 0;
};
