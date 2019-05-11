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
	void AddTile(TScriptInterface<IWorldTile> Tile);
	void RemoveTile(TScriptInterface<IWorldTile> Tile);

private:
	UPROPERTY(VisibleAnywhere)
	TSet<FAiTileData> ExpansionTiles;
};
