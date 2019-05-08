// Fill out your copyright notice in the Description page of Project Settings.

#include "TileCoordinates.h"

FTileCoordinates::FTileCoordinates(const int Row, const int Column)
{
	Init(Row, Column);
}

void FTileCoordinates::Init(int R, int C)
{
	check(R >= 0);
	check(C >= 0);
	Row = R;
	Column = C;
}

TArray<FTileCoordinates> FTileCoordinates::GetIncidentCoordinates(const int TotalRows, const int TotalColumns, const int Distance) const
{
	TArray<FTileCoordinates> Results;
	for (auto R = Row - Distance; R <= Row + Distance; ++R)
	{
		for (auto C = Column - Distance; C <= Column+Distance; ++C)
		{
			if (!IsEqualToCurrent(R, C)
				&& IsValidValue(R, TotalRows)
				&& IsValidValue(C, TotalColumns))
			{
				Results.Emplace(R, C);
			}
		}
	}
	return Results;
}

int FTileCoordinates::GetRow() const
{
	return Row;
}

int FTileCoordinates::GetColumn() const
{
	return Column;
}

bool FTileCoordinates::IsValidValue(const int Value, const int Max) const
{
	return Value >= 0 && Value < Max;
}

bool FTileCoordinates::IsEqualToCurrent(const int OtherRow, const int OtherColumn) const
{
	return Row == OtherRow && Column == OtherColumn;
}
