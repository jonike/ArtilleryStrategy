// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles.h"
#include "Interfaces/WorldTile.h"

TSet<UObject*> UTiles::FilterOnlyTilesWithoutBuildings(const TSet<UObject*>& Tiles)
{
	TSet<UObject*> Results;
	for (const auto& TileObject : Tiles)
	{
		if (const auto Tile = Cast<IWorldTile>(TileObject))
		{
			if (!Tile->HasBuilding())
			{
				Results.Emplace(TileObject);
			}
		}
	}
	return Results;
}
