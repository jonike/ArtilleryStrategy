// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"

TScriptInterface<IGridPlatform> ADefaultGS::GetTileForCapital() const
{
	const auto Row = FMath::RandRange(0, Matrix.GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix.GetColumns() - 1);
	return Matrix(Row, Column);
}
