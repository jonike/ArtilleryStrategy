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

	UPROPERTY(VisibleInstanceOnly)
	int Priority = 0;

	UPROPERTY(VisibleInstanceOnly)
	int Distance = 0;

	UPROPERTY(VisibleInstanceOnly)
	bool bHasResources = false;

	UPROPERTY(VisibleInstanceOnly)
	bool bNearEnemy = false;

	UPROPERTY(VisibleInstanceOnly)
	bool bHighPosition = false;

	TScriptInterface<IWorldTile> Tile;
};

bool operator==(const FAiTileData& Lhs, const FAiTileData& Rhs);
