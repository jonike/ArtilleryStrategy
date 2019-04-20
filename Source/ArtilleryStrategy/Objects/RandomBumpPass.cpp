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
	const auto RandomColumn = FMath::RandRange(0, Columns-1);
	check(Params.HeightMatrix.IsValidIndex(RandomRow, RandomColumn));
	return MakeTuple(RandomRow, RandomColumn);
}

void URandomBumpPass::AddBumpInPosition(FWorldParams& Params, const int CenterRow, const int CenterColumn) const
{
	for (auto CenterDistance = 0; CenterDistance < BumpOffsets.Num(); ++CenterDistance)
	{
		// TODO: offsets only on direct lines
		TryToApplyOffset(Params, CenterRow - CenterDistance, CenterColumn - CenterDistance, BumpOffsets[CenterDistance]);
		TryToApplyOffset(Params, CenterRow - CenterDistance, CenterColumn + CenterDistance, BumpOffsets[CenterDistance]);
		TryToApplyOffset(Params, CenterRow + CenterDistance, CenterColumn - CenterDistance, BumpOffsets[CenterDistance]);
		TryToApplyOffset(Params, CenterRow + CenterDistance, CenterColumn + CenterDistance, BumpOffsets[CenterDistance]);
	}
}

void URandomBumpPass::TryToApplyOffset(FWorldParams& Params, const int Row, const int Column, const int Offset) const
{
	if (Params.HeightMatrix.IsValidIndex(Row, Column))
	{
		Params.HeightMatrix.Get(Row, Column) += Offset;
	}
}
