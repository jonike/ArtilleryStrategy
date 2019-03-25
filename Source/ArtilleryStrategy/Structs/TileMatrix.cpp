// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMatrix.h"

void FTileMatrix::Resize(const int Rows, const int Columns)
{
	Matrix.AddDefaulted(Rows);
	for (auto& Row : Matrix)
	{
		Row.Storage.AddDefaulted(Columns);
	}
	MatrixRows = Rows;
	MatrixColumns = Columns;
}

TScriptInterface<IGridPlatform>& FTileMatrix::operator()(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

const TScriptInterface<IGridPlatform>& FTileMatrix::operator()(const int Row, const int Column) const
{
	return Matrix[Row].Storage[Column];
}
