// Fill out your copyright notice in the Description page of Project Settings.

#include "OffsetSmoothingPass.h"
#include "Structs/WorldParams.h"

void UOffsetSmoothingPass::GenerateWorld(FWorldParams& Params)
{
	AppropriateRanges.Resize(Params.HeightMatrix.GetRows(), Params.HeightMatrix.GetColumns());
	CalculateAppropriateLevels(Params);
	while (!IsSmoothingComplete(Params))
	{
		SmoothAll(Params);
	}
}

void UOffsetSmoothingPass::CalculateAppropriateLevels(FWorldParams& Params)
{
	for (auto Row = 0; Row < Params.HeightMatrix.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.HeightMatrix.GetColumns(); ++Column)
		{
			AppropriateRanges.Get(Row, Column) = GetAppropriateLevels(Params, Row, Column);
		}
	}
}

void UOffsetSmoothingPass::AdjustAllHeights(FWorldParams& Params)
{
	for (auto Row = 0; Row < Params.HeightMatrix.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.HeightMatrix.GetColumns(); ++Column)
		{
			AdjustHeight(Params, Row, Column);
		}
	}
}

void UOffsetSmoothingPass::SmoothAll(FWorldParams& Params)
{
	AdjustAllHeights(Params);
	CalculateAppropriateLevels(Params);
}

void UOffsetSmoothingPass::AdjustHeight(FWorldParams& Params, const int Row, const int Column)
{
	if (!IsAppropriatePosition(Params, Row, Column))
	{
		auto& Height = Params.HeightMatrix.Get(Row, Column);
		const auto& Range = AppropriateRanges.Get(Row, Column);
		if (Range.IsLess(Height))
		{
			Height = Range.GetMin();
		}
		else if (Range.IsGreater(Height))
		{
			Height = Range.GetMax();
		}
	}
}

bool UOffsetSmoothingPass::IsAppropriatePosition(const FWorldParams& Params, const int Row, const int Column) const
{
	const auto& Range = AppropriateRanges.Get(Row, Column);
	const auto Height = Params.HeightMatrix.Get(Row, Column);
	return Range.IsInRange(Height);
}

bool UOffsetSmoothingPass::IsSmoothingComplete(const FWorldParams& Params) const
{
	for (auto Row = 0; Row < AppropriateRanges.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < AppropriateRanges.GetColumns(); ++Column)
		{
			if (!IsAppropriatePosition(Params, Row, Column))
			{
				return false;
			}
		}
	}
	return true;
}

TValueRange<int> UOffsetSmoothingPass::GetAppropriateLevels(const FWorldParams& Params, const int TileRow, const int TileColumn) const
{
	TValueRange<int> Range(-INT_MAX, INT_MAX);
	for (auto Row = TileRow - 1; Row <= TileRow + 1; ++Row)
	{
		for (auto Column = TileColumn - 1; Column <= TileColumn + 1; ++Column)
		{
			if (Row == TileRow && Column == TileColumn || !Params.HeightMatrix.IsValidIndex(Row, Column))
			{
				continue;
			}
			const auto NeighborHeight = Params.HeightMatrix.Get(Row, Column);
			if (Range.GetMin() < NeighborHeight - MaxHeightDifference)
			{
				Range.SetMin(NeighborHeight - MaxHeightDifference);
			}
			else if (Range.GetMax() > NeighborHeight + MaxHeightDifference)
			{
				Range.SetMax(NeighborHeight + MaxHeightDifference);
			}
		}
	}
	return Range;
}
