// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MatrixContainer.h"
#include "WorldParams.generated.h"

class UTileMatrix;
/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FWorldParams
{
	GENERATED_BODY()

	void Initialize(UObject* Context);
	void Initialize(UObject* Context, int Rows, int Columns);

	int GetRows() const;
	int GetColumns() const;

	UTileMatrix* GetTileMatrix() const;
	UWorld* GetCurrentWorld() const;
	TMatrixContainer<int> GetHeightMatrix() const;

	UPROPERTY(VisibleInstanceOnly)
	UTileMatrix* TileMatrix;

	UPROPERTY()
	UWorld* CurrentWorld;

	// TODO: change to TMatrixContainer<FTileData> DataMatrix;
	TMatrixContainer<int> HeightMatrix;

private:
	int Rows = 0;
	int Columns = 0;
};
