// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "Structs/MatrixContainer.h"
#include "Structs/ValueRange.h"
#include "OffsetSmoothingPass.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UOffsetSmoothingPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;
	void CalculateAppropriateLevels(FWorldParams& Params);
	void AdjustAllHeights(FWorldParams& Params);

private:
	UPROPERTY(EditAnywhere)
	int MaxHeightDifference = 2;

	TMatrixContainer<TValueRange<int>> AppropriateRanges;

	void SmoothAll(FWorldParams& Params);
	void AdjustHeight(FWorldParams& Params, int Row, int Column);

	bool IsAppropriatePosition(const FWorldParams& Params, int Row, int Column) const;
	bool IsSmoothingComplete(const FWorldParams& Params) const;
	TValueRange<int> GetAppropriateLevels(const FWorldParams& Params, int TileRow, int TileColumn) const;
};
