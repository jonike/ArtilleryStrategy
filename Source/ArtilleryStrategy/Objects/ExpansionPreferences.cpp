// Fill out your copyright notice in the Description page of Project Settings.

#include "ExpansionPreferences.h"

void UExpansionPreferences::AddTile(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	ExpansionTiles.Emplace(Data);
}

void UExpansionPreferences::RemoveTile(const TScriptInterface<IWorldTile> Tile)
{
	FAiTileData Data;
	Data.Tile = Tile;
	ExpansionTiles.Remove(Data);
}

FAiTileData UExpansionPreferences::GetBest()
{
	const auto Result = *ExpansionTiles.CreateConstIterator();
	ExpansionTiles.Remove(Result);
	return Result;
}
