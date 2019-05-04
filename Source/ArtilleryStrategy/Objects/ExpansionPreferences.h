// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/AiTileData.h"
#include "ExpansionPreferences.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UExpansionPreferences : public UObject
{
	GENERATED_BODY()

public:
	void AddTileToBuy(TScriptInterface<IWorldTile> Tile);
	void AddOwnedTile(TScriptInterface<IWorldTile> Tile);
	void RemoveOwnedTile(TScriptInterface<IWorldTile> Tile);

private:
	TSet<FAiTileData> TilesToBuy;
	TSet<FAiTileData> OwnedTiles;
};
