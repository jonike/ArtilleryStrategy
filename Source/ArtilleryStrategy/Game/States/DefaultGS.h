// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GridPlatform.h"
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

	TScriptInterface<IGridPlatform> GetTileForCapital() const;

protected:
	void PostInitializeComponents() override;

private:
	UFUNCTION()
	void ReceiveOnGridGenerationStarted(int Rows, int Columns);
	UFUNCTION()
	void ReceiveOnTileGenerated(TScriptInterface<IGridPlatform> Tile, int Row, int Column);

	UPROPERTY()
	UTileMatrix* Matrix;

	void AddTile(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column) const { (*Matrix)(Row, Column) = Tile; }
	void ResizeTileMatrix(const int Rows, const int Columns) const { Matrix->Resize(Rows, Columns); }

	UGridGenerator* GetGridGenerator() const;
};
