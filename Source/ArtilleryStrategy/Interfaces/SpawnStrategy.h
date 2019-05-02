// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "SpawnStrategy.generated.h"

class UTileMatrix;
class IWorldTile;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDEPRECATED_SpawnStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Strategy for spawning new items in the world
 */
class ARTILLERYSTRATEGY_API IDEPRECATED_SpawnStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTileMatrix(UTileMatrix* Matrix) = 0;

	virtual TScriptInterface<IWorldTile> GetNextSpawnPoint() const = 0;
};
