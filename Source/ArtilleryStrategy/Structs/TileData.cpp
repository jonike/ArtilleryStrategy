// Fill out your copyright notice in the Description page of Project Settings.

#include "TileData.h"
#include "Libraries/ASLibrary.h"
#include "Objects/TileMatrix.h"

FTileData::FTileData(const FTileCoordinates TileCoordinates)
{
	Coordinates = TileCoordinates;
}

TArray<TScriptInterface<IWorldTile>> FTileData::GetAdjacentTiles(const UObject* Context) const
{
	const auto WorldParams = UASLibrary::GetWorldParams(Context);
	const auto AdjacentCoordinates = Coordinates.GetIncidentCoordinates(WorldParams.GetRows(), WorldParams.GetColumns());
	TArray<TScriptInterface<IWorldTile>> Results;
	for (const auto& TileCoordinates : AdjacentCoordinates)
	{
		const auto AdjacentTile = WorldParams.GetTileMatrix()->Get(TileCoordinates.GetRow(), TileCoordinates.GetColumn());
		Results.Add(AdjacentTile);
	}
	return Results;
}
