// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptInterface.h"
#include "TileMatrix.generated.h"

class IGridPlatform;

/**
 * 
 */
USTRUCT()
struct ARTILLERYSTRATEGY_API FTileMatrix
{
	GENERATED_BODY()

public:
	void Resize(int Rows, int Columns);

	int GetRows() const { return MatrixRows; }
	int GetColumns() const { return MatrixColumns; }

	TScriptInterface<IGridPlatform>& operator()(int Row, int Column);
	const TScriptInterface<IGridPlatform>& operator()(int Row, int Column) const;

private:
	struct FRow
	{
		TArray<TScriptInterface<IGridPlatform>> Storage;
	};

	int MatrixRows = 0;
	int MatrixColumns = 0;

	TArray<FRow> Matrix;
};
