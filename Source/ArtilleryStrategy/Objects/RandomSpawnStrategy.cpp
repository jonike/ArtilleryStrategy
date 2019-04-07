// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomSpawnStrategy.h"
#include "TileMatrix.h"

void URandomSpawnStrategy::SetTileMatrix(UTileMatrix* Matrix)
{
	TileMatrix = Matrix;
}

TScriptInterface<IGridPlatform> URandomSpawnStrategy::GetNextSpawnPoint() const
{
	check(TileMatrix);
	const auto Row = FMath::RandRange(0, TileMatrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, TileMatrix->GetColumns() - 1);
	return TileMatrix->Get(Row, Column);
}
