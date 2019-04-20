// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScriptInterface.h"
#include "Interfaces/GridPlatform.h"
#include "TileMatrix.generated.h"

/**
 * 
 */
// TODO: derive from TMatrixContainer?
UCLASS(BlueprintType, DefaultToInstanced)
class ARTILLERYSTRATEGY_API UTileMatrix : public UObject
{
	GENERATED_BODY()

public:
	void Resize(int Rows, int Columns);

	int GetRows() const { return MatrixRows; }
	int GetColumns() const { return MatrixColumns; }
	bool IsValidIndex(int Row, int Column) const;

	// TODO: provide SET methods
	TScriptInterface<IGridPlatform>& Get(int Row, int Column);
	const TScriptInterface<IGridPlatform>& Get(int Row, int Column) const;

	TScriptInterface<IGridPlatform>& operator()(int Row, int Column);
	const TScriptInterface<IGridPlatform>& operator()(int Row, int Column) const;

private:
	struct FRow
	{
		TArray<TScriptInterface<IGridPlatform>> Storage;
	};

	UPROPERTY(Category = "Size", VisibleAnywhere)
	int MatrixRows = 0;

	UPROPERTY(Category = "Size", VisibleAnywhere)
	int MatrixColumns = 0;

	TArray<FRow> Matrix;
};
