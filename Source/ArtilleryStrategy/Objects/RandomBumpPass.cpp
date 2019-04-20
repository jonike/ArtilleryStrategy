// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomBumpPass.h"
#include "Structs/WorldParams.h"

void URandomBumpPass::GenerateWorld(FWorldParams& Params)
{
	for (auto Times = 0; Times < BumpAmount; ++Times)
	{
		const auto Indexes = GetRandomIndexes(Params);
		AddBumpInPosition(Params, Indexes.Key, Indexes.Value);
	}
}

TPair<int, int> URandomBumpPass::GetRandomIndexes(const FWorldParams& Params) const
{
	const auto Rows = Params.HeightMatrix.GetRows();
	const auto Columns = Params.HeightMatrix.GetColumns();
	const auto RandomRow = FMath::RandRange(0, Rows - 1);
	const auto RandomColumn = FMath::RandRange(0, Columns - 1);
	check(Params.HeightMatrix.IsValidIndex(RandomRow, RandomColumn));
	return MakeTuple(RandomRow, RandomColumn);
}

void URandomBumpPass::AddBumpInPosition(FWorldParams& Params, const int CenterRow, const int CenterColumn) const
{
	for (auto CenterDistance = 0; CenterDistance < BumpOffsets.Num(); ++CenterDistance)
	{
		const auto FromRow = FMath::Clamp(CenterRow - CenterDistance, 0, Params.HeightMatrix.GetRows() - 1);
		const auto ToRow = FMath::Clamp(CenterRow + CenterDistance, 0, Params.HeightMatrix.GetRows() - 1);
		const auto FromColumn = FMath::Clamp(CenterColumn - CenterDistance, 0, Params.HeightMatrix.GetColumns() - 1);
		const auto ToColumn = FMath::Clamp(CenterColumn + CenterDistance, 0, Params.HeightMatrix.GetColumns() - 1);
		for (auto Row = FromRow; Row <= ToRow; ++Row)
		{
			for (auto Column = FromColumn; Column <= ToColumn; ++Column)
			{
				FIntVector Distance(Row - CenterRow, Column - CenterColumn, 0);
				if (Distance.Size() == CenterDistance)
				{
					ApplyOffset(Params, Row, Column, BumpOffsets[CenterDistance]);
				}
			}
		}
	}
}

void URandomBumpPass::ApplyOffset(FWorldParams& Params, const int Row, const int Column, const int Offset) const
{
	Params.HeightMatrix.Get(Row, Column) += Offset;
}
