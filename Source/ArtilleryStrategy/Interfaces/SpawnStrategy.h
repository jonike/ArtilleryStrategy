// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpawnStrategy.generated.h"

class UTileMatrix;
class IGridPlatform;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpawnStrategy : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API ISpawnStrategy
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTileMatrix(UTileMatrix* Matrix) = 0;

	virtual TScriptInterface<IGridPlatform> GetNextSpawnPoint() const = 0;
};
