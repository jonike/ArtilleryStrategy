// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Interfaces/WorldTile.h"
#include "AiTileData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FAiTileData
{
	GENERATED_BODY()

	int Priority = 0;
	int Distance = 0;

	bool bHasResources = false;
	bool bNearEnemy = false;
	bool bHighPosition = false;

	TScriptInterface<IWorldTile> Tile;
};

bool operator==(const FAiTileData& Lhs, const FAiTileData& Rhs);
