// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Building.h"
#include "Structs/ResourceDeposit.h"
#include "WorldTile.generated.h"

struct FTileData;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWorldTile : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ARTILLERYSTRATEGY_API IWorldTile
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetTileData(FTileData Data) = 0;
	virtual const FTileData& GetTileData() = 0;

	virtual FVector GetBuildingSpawnLocation() const = 0;
	virtual bool HasBuilding() const = 0;
	virtual void SetBuilding(TScriptInterface<IBuilding> Building) = 0;
	virtual TScriptInterface<IBuilding> SpawnBuilding(TSubclassOf<AActor> BuildingClass) = 0;

	virtual TSet<FResourceDeposit>& GetResourceDeposits() = 0;
	virtual bool HasResourceDeposits() const = 0;
	virtual void SetResourceDeposits(FResourceDeposit& Deposit) = 0;
};
