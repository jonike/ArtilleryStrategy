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

	FAiTileData* Get(TScriptInterface<IWorldTile> Tile);
	const FAiTileData* Get(TScriptInterface<IWorldTile> Tile) const;

	const TSet<FAiTileData>& GetTilesToBuy() const;
	const TSet<FAiTileData>& GetOwnedTiles() const;

private:
	UPROPERTY(VisibleInstanceOnly)
	TSet<FAiTileData> TilesToBuy;

	UPROPERTY(VisibleInstanceOnly)
	TSet<FAiTileData> OwnedTiles;
};
