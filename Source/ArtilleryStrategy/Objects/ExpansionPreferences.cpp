// Fill out your copyright notice in the Description page of Project Settings.

#include "ExpansionPreferences.h"

void UExpansionPreferences::AddTileToBuy(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	TilesToBuy.Emplace(Data);
}

void UExpansionPreferences::AddOwnedTile(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	TilesToBuy.Remove(Data);
	OwnedTiles.Emplace(Data);
}

void UExpansionPreferences::RemoveOwnedTile(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	OwnedTiles.Remove(Data);
}

FAiTileData* UExpansionPreferences::Get(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	auto Result = TilesToBuy.Find(Data);
	if (Result)
	{
		return Result;
	}
	Result = OwnedTiles.Find(Data);
	if (Result)
	{
		return Result;
	}
	return nullptr;
}

const FAiTileData* UExpansionPreferences::Get(const TScriptInterface<IWorldTile> Tile) const
{
	FAiTileData Data;
	Data.Tile = Tile;
	auto Result = TilesToBuy.Find(Data);
	if (Result)
	{
		return Result;
	}
	Result = OwnedTiles.Find(Data);
	if (Result)
	{
		return Result;
	}
	return nullptr;
}
