// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tiles.generated.h"

class IBuilding;
class IWorldTile;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UTiles : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	using FTileFunction = TFunction<void(TScriptInterface<IWorldTile>)>;

	static TSet<UObject*> FilterOnlyTilesWithoutBuildings(const TSet<UObject*>& Tiles);

	static void ForEachTileInRadius(TScriptInterface<IWorldTile> Center, int Radius, FTileFunction Function);

	static TSet<TScriptInterface<IWorldTile>> GetTilesInRadius(TScriptInterface<IWorldTile> Center, int Radius);

	static TSet<TScriptInterface<IBuilding>> GetBuildingsInRadius(TScriptInterface<IWorldTile> Center, int Radius);
};
