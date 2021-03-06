// Fill out your copyright notice in the Description page of Project Settings.

#include "TilesLibrary.h"
#include "Interfaces/WorldTile.h"
#include "CoreLibrary.h"
#include "Structs/TileData.h"
#include "Structs/WorldParams.h"
#include "Objects/TileMatrix.h"

TSet<UObject*> UTilesLibrary::FilterOnlyTilesWithoutBuildings(const TSet<UObject*>& Tiles)
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

void UTilesLibrary::ForEachTileInRadius(TScriptInterface<IWorldTile> Center, const int Radius, const FTileFunction Function)
{
	check(Center);
	check(Function);
	const auto& Params = UCoreLibrary::GetWorldParams(Center.GetObject());

	const auto CenterRow = Center->GetTileData().Coordinates.GetRow();
	const auto CenterColumn = Center->GetTileData().Coordinates.GetColumn();

	const auto MinRow = FMath::Max(CenterRow - Radius, 0);
	const auto MinColumn = FMath::Max(CenterColumn - Radius, 0);

	const auto MaxRow = FMath::Min(CenterRow + Radius, Params.GetRows() - 1);
	const auto MaxColumn = FMath::Min(CenterColumn + Radius, Params.GetColumns() - 1);
	for (auto Row = MinRow; Row <= MaxRow; ++Row)
	{
		for (auto Column = MinColumn; Column <= MaxColumn; ++Column)
		{
			const auto DeltaRow = FMath::Abs(Row - CenterRow);
			const auto DeltaColumn = FMath::Abs(Column - CenterColumn);
			if (DeltaRow + DeltaColumn <= Radius)
			{
				const auto Tile = Params.GetTileMatrix()->Get(Row, Column);
				Function(Tile);
			}
		}
	}
}

TSet<TScriptInterface<IWorldTile>> UTilesLibrary::GetTilesInRadius(const TScriptInterface<IWorldTile> Center, const int Radius)
{
	TSet<TScriptInterface<IWorldTile>> Tiles;
	ForEachTileInRadius(Center, Radius, [&Tiles](const TScriptInterface<IWorldTile> Tile)
	{
		if (!Tile.GetObject()->IsPendingKill())
		{
			Tiles.Add(Tile);
		}
	});
	return Tiles;
}

TSet<TScriptInterface<IBuilding>> UTilesLibrary::GetBuildingsInRadius(const TScriptInterface<IWorldTile> Center, const int Radius)
{
	TSet<TScriptInterface<IBuilding>> Buildings;
	ForEachTileInRadius(Center, Radius, [&Buildings](const TScriptInterface<IWorldTile> Tile)
	{
		if (Tile->HasBuilding()
			&& !Tile.GetObject()->IsPendingKill()
			&& !Tile->GetBuilding().GetObject()->IsPendingKill())
		{
			Buildings.Add(Tile->GetBuilding());
		}
	});
	return Buildings;
}
