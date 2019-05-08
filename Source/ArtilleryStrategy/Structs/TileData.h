// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileCoordinates.h"
#include "Interfaces/WorldTile.h"
#include "TileData.generated.h"

/**
 * Structure to hold all data about tile even before its created
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FTileData
{
	GENERATED_BODY()

	FTileData() = default;
	explicit FTileData(FTileCoordinates TileCoordinates);

	TArray<TScriptInterface<IWorldTile>> GetAdjacentTiles(const UObject* Context) const;

	UPROPERTY(VisibleInstanceOnly)
	FTileCoordinates Coordinates;
};
