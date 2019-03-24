// Fill out your copyright notice in the Description page of Project Settings.


#include "TileMatrix.h"

void UTileMatrix::Reserve(const int Rows, const int Columns)
{
	Matrix.Reserve(Rows);
	for (auto Row : Matrix)
	{
		Row.Storage.Reserve(Columns);
	}
	MatrixRows = Rows;
	MatrixColumns = Columns;
}

TScriptInterface<IGridPlatform>& UTileMatrix::operator()(const int Row, const int Column)
{
	return Matrix[Row].Storage[Column];
}

const TScriptInterface<IGridPlatform>& UTileMatrix::operator()(const int Row, const int Column) const
{
	return Matrix[Row].Storage[Column];
}
