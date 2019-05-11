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
	// TODO: avoid creating array from set
	const auto TilesArray = ExpansionTiles.Array();
	check(TilesArray.Num() > 0);
	const auto Index = FMath::RandRange(0, ExpansionTiles.Num() - 1);
	const auto ReturnValue = TilesArray[Index];
	ExpansionTiles.Remove(ReturnValue);
	return ReturnValue;
}
