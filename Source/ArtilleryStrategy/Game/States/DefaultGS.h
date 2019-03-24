// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Objects/TileMatrix.h"
#include "DefaultGS.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	void AddTile(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column) { Matrix(Row, Column) = Tile; }
	void ReserveTileMatrix(const int Rows, const int Columns) { Matrix.Reserve(Rows, Columns); }
	TScriptInterface<IGridPlatform> GetTileForCapital() const;

private:
	UTileMatrix Matrix;
};
