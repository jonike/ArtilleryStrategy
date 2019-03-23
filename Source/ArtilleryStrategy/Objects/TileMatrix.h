// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptInterface.h"
#include "TileMatrix.generated.h"

class IGridPlatform;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UTileMatrix : public UObject
{
	GENERATED_BODY()

public:
	void Reserve(int Rows, int Columns);
	void Add(TScriptInterface<IGridPlatform> Tile);

	TScriptInterface<IGridPlatform>& operator()(int Row, int Column);
	const TScriptInterface<IGridPlatform>& operator()(int Row, int Column) const;

private:
	struct FRow
	{
		TArray<TScriptInterface<IGridPlatform>> Storage;
	};

	TArray<FRow> Matrix;
};
