// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "Interfaces/GridPlatform.h"
#include "RandomVerticalOffsetPass.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API URandomVerticalOffsetPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	virtual void OffsetTile(TScriptInterface<IGridPlatform> Tile);
	virtual float GetRandomOffset(float Min, float Max, float Step);

private:
	UPROPERTY(Category = "Offset", EditDefaultsOnly)
	float MinVerticalOffset = -500.f;

	UPROPERTY(Category = "Offset", EditDefaultsOnly)
	float MaxVerticalOffset = 500.f;

	UPROPERTY(Category = "Offset", EditDefaultsOnly)
	float OffsetStep = 100.f;

	void OffsetAllTiles(const FWorldParams& Params);
};
