// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMatrix.h"

void UTileMatrix::Resize(const int Rows, const int Columns)
{
	Matrix.AddDefaulted(Rows);
	for (auto& Row : Matrix)
	{
		Row.Storage.AddDefaulted(Columns);
	}
	MatrixRows = Rows;
	MatrixColumns = Columns;
}

TScriptInterface<IGridPlatform>& UTileMatrix::Get(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

auto UTileMatrix::Get(const int Row, int Column) const -> const TScriptInterface<IGridPlatform>&
{
	return Matrix[Row].Storage[Column];
}

TScriptInterface<IGridPlatform>& UTileMatrix::operator()(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

const TScriptInterface<IGridPlatform>& UTileMatrix::operator()(const int Row, const int Column) const
{
	return Matrix[Row].Storage[Column];
}
