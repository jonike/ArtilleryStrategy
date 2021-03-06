// Fill out your copyright notice in the Description page of Project Settings.

#include "TileMatrix.h"

void UTileMatrix::Resize(const int Rows, const int Columns)
{
	Matrix.SetNum(Rows);
	for (auto& Row : Matrix)
	{
		Row.Storage.SetNum(Columns);
	}
	MatrixRows = Rows;
	MatrixColumns = Columns;
}

bool UTileMatrix::IsValidIndex(const int Row, const int Column) const
{
	if (!Matrix.IsValidIndex(Row))
	{
		return false;
	}
	return Matrix[Row].Storage.IsValidIndex(Column);
}

TScriptInterface<IWorldTile>& UTileMatrix::Get(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

auto UTileMatrix::Get(const int Row, const int Column) const -> const TScriptInterface<IWorldTile>&
{
	return Matrix[Row].Storage[Column];
}

TScriptInterface<IWorldTile>& UTileMatrix::operator()(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

const TScriptInterface<IWorldTile>& UTileMatrix::operator()(const int Row, const int Column) const
{
	return Matrix[Row].Storage[Column];
}
