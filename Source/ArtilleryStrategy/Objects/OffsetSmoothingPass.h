// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "Interfaces/GridPlatform.h"
#include "OffsetSmoothingPass.generated.h"

/**
 * 
 */
UCLASS(Deprecated)
class ARTILLERYSTRATEGY_API UDEPRECATED_OffsetSmoothingPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	virtual void SmoothTile(TScriptInterface<IGridPlatform> Tile, int Deviance);
	virtual int CalculateDevianceLevel(const FWorldParams& Params, int TileRow, int TileColumn);

private:
	UPROPERTY(Category = "Range", EditDefaultsOnly)
	int SmoothRadius = 2;

	UPROPERTY(Category = "Tolerance", EditDefaultsOnly)
	int MinDevianceLevel = -2;

	UPROPERTY(Category = "Tolerance", EditDefaultsOnly)
	int MaxDevianceLevel = 2;

	// TODO: value depends on offset for different levels in RandomVerticalOffsetPass
	UPROPERTY(Category = "Smoothing", EditDefaultsOnly)
	float OffsetPerDeviancePoint = 100.f;

	int CalculateDevianceForPair(TScriptInterface<IGridPlatform> AnalyzedTile, TScriptInterface<IGridPlatform> NeighborTile) const;
};
