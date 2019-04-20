// Fill out your copyright notice in the Description page of Project Settings.

#include "OffsetSmoothingPass.h"
#include "Structs/WorldParams.h"

void UOffsetSmoothingPass::GenerateWorld(FWorldParams& Params)
{
	AppropriateLevels.Resize(Params.HeightMatrix.GetRows(), Params.HeightMatrix.GetColumns());
	do
	{
		SmoothAll(Params);
	}
	while (!IsSmoothingComplete(Params));
}

void UOffsetSmoothingPass::SmoothAll(FWorldParams& Params)
{
	// TODO: extract two methods
	for (auto Row = 0; Row < Params.HeightMatrix.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.HeightMatrix.GetColumns(); ++Column)
		{
			AppropriateLevels.Get(Row, Column) = GetAppropriateLevels(Params, Row, Column);
		}
	}

	for (auto Row = 0; Row < Params.HeightMatrix.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.HeightMatrix.GetColumns(); ++Column)
		{
			AdjustHeight(Params, Row, Column);
		}
	}
}

void UOffsetSmoothingPass::AdjustHeight(FWorldParams& Params, const int Row, const int Column)
{
	if (!IsAppropriatePosition(Params, Row, Column))
	{
		auto& Height = Params.HeightMatrix.Get(Row, Column);
		const auto& Levels = AppropriateLevels.Get(Row, Column);
		if (Height < Levels.Min)
		{
			Height = Levels.Min;
		}
		else
		{
			Height = Levels.Max;
		}
	}
}

bool UOffsetSmoothingPass::IsAppropriatePosition(const FWorldParams& Params, const int Row, const int Column) const
{
	const auto& Levels = AppropriateLevels.Get(Row, Column);
	const auto Height = Params.HeightMatrix.Get(Row, Column);
	return Height >= Levels.Min && Height <= Levels.Max;
}

bool UOffsetSmoothingPass::IsSmoothingComplete(const FWorldParams& Params) const
{
	for (auto Row = 0; Row < AppropriateLevels.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < AppropriateLevels.GetColumns(); ++Column)
		{
			if (!IsAppropriatePosition(Params, Row, Column))
			{
				return false;
			}
		}
	}
	return true;
}

UOffsetSmoothingPass::FRange UOffsetSmoothingPass::GetAppropriateLevels(const FWorldParams& Params, const int TileRow, const int TileColumn) const
{
	FRange Levels;
	Levels.Set(Params.HeightMatrix.Get(TileRow, TileColumn));
	for (auto Row = TileRow - 1; Row <= TileRow + 1; ++Row)
	{
		for (auto Column = TileColumn - 1; Column <= TileColumn + 1; ++Column)
		{
			if (Row == TileRow && Column == TileColumn || !Params.HeightMatrix.IsValidIndex(Row, Column))
			{
				continue;
			}
			const auto NeighborHeight = Params.HeightMatrix.Get(Row, Column);
			if (NeighborHeight + MaxHeightDifference < Levels.Min)
			{
				Levels.Min = NeighborHeight + MaxHeightDifference;
			}
			else if (NeighborHeight - MaxHeightDifference > Levels.Max)
			{
				Levels.Max = NeighborHeight - MaxHeightDifference;
			}
		}
	}
	return Levels;
}
;
