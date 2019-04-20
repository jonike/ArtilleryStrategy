// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomVerticalOffsetPass.h"
#include "Structs/WorldParams.h"
#include "TileMatrix.h"

void URandomVerticalOffsetPass::GenerateWorld(FWorldParams& Params)
{
	OffsetAllTiles(Params);
}

void URandomVerticalOffsetPass::OffsetTile(FWorldParams& Params, const int Row, const int Column)
{
	const auto RandomOffset = GetRandomOffset(MinVerticalOffset, MaxVerticalOffset, OffsetStep);
	Params.HeightMatrix.Get(Row, Column) += RandomOffset;
}

float URandomVerticalOffsetPass::GetRandomOffset(const float Min, const float Max, const float Step)
{
	const auto Steps = static_cast<int>((Max - Min) / Step);
	const auto RandomStep = FMath::RandRange(0, Steps);
	return Min + Step * RandomStep;
}

void URandomVerticalOffsetPass::OffsetAllTiles(FWorldParams& Params)
{
	const auto* TileMatrix = Params.TileMatrix;
	for (auto Row = 0; Row < TileMatrix->GetRows(); ++Row)
	{
		for (auto Column = 0; Column < TileMatrix->GetColumns(); ++Column)
		{
			OffsetTile(Params, Row, Column);
		}
	}
}
