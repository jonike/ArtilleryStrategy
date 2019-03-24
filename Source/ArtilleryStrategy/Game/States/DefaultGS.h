// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Objects/TileMatrix.h"
#include "DefaultGS.generated.h"

class UGridGenerator;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADefaultGS();

	TScriptInterface<IGridPlatform> GetTileForCapital() const;

protected:
	void BeginPlay() override;

private:
	UPROPERTY()
	UTileMatrix* Matrix;

	UFUNCTION()
	void WhenGridGenerationStarted(int Rows, int Columns);
	UFUNCTION()
	void WhenTileGenerated(TScriptInterface<IGridPlatform> Tile, int Row, int Column);

	void AddTile(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column) const { (*Matrix)(Row, Column) = Tile; }
	void ReserveTileMatrix(const int Rows, const int Columns) const { Matrix->Reserve(Rows, Columns); }

	UGridGenerator* GetGridGenerator() const;
};
