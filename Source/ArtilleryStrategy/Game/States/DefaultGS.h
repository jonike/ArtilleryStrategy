// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GridPlatform.h"
#include "Objects/TileMatrix.h"
#include "Components/CapitalPlacementGenerator.h"
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
	void PostInitializeComponents() override;
	void BeginPlay() override;

private:
	UFUNCTION()
	void ReceiveOnGridGenerationStarted(int Rows, int Columns);
	UFUNCTION()
	void ReceiveOnTileGenerated(TScriptInterface<IGridPlatform> Tile, int Row, int Column);

	UPROPERTY(Category = "Tiles", VisibleAnywhere)
	UTileMatrix* Matrix;

	UPROPERTY(EditAnywhere)
	UGridGenerator* GridGenerator;

	UPROPERTY(EditAnywhere)
	UCapitalPlacementGenerator* CapitalPlacementGenerator;

	void AddTile(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column) const { Matrix->Get(Row, Column) = Tile; }
	void ResizeTileMatrix(const int Rows, const int Columns) const { Matrix->Resize(Rows, Columns); }

	UGridGenerator* GetGridGenerator() const;
	UCapitalPlacementGenerator* GetCapitalPlacementGenerator() const;
};
