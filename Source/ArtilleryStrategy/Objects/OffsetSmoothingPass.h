// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "Structs/MatrixContainer.h"
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

private:
	struct FRange
	{
		void Set(const int MinValue, const int MaxValue)
		{
			Min = MinValue;
			Max = MaxValue;
		}

		void Set(const int Value)
		{
			Set(Value, Value);
		}

		int Min;
		int Max;
	};

	UPROPERTY(EditAnywhere)
	int MaxHeightDifference = 1;

	TMatrixContainer<FRange> AppropriateLevels;

	void SmoothAll(FWorldParams& Params);
	void AdjustHeight(FWorldParams& Params, int Row, int Column);

	bool IsAppropriatePosition(const FWorldParams& Params, int Row, int Column) const;
	bool IsSmoothingComplete(const FWorldParams& Params) const;
	FRange GetAppropriateLevels(const FWorldParams& Params, int TileRow, int TileColumn) const;
};
