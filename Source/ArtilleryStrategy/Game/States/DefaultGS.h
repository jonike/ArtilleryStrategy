// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Interfaces/GridPlatform.h"
#include "Objects/TileMatrix.h"
#include "Components/CapitalPlacementGenerator.h"
#include "DefaultGS.generated.h"

class IMapGenerator;
class UResourceDepositGenerator;
class ISpawnStrategy;
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

	TScriptInterface<ISpawnStrategy> GetCapitalSpawnStrategy() const;
	TScriptInterface<ISpawnStrategy> GetDepositSpawnStrategy() const;

protected:
	void PostInitializeComponents() override;

private:
	UPROPERTY(Category = "Tiles", VisibleAnywhere)
	UTileMatrix* Matrix;

	UPROPERTY(Category = "Generation", EditAnywhere)
	UGridGenerator* GridGenerator;

	UPROPERTY(Category = "Generation", EditAnywhere)
	TArray<TScriptInterface<IMapGenerator>> MapGenerators; // TODO: add array of types and then populate array of objects

	// Capital placement
	UPROPERTY(EditAnywhere)
	UCapitalPlacementGenerator* CapitalPlacementGenerator;
	UPROPERTY(Category = "Procedural generation", EditDefaultsOnly, meta = (MustImplement = "SpawnStrategy"))
	TSubclassOf<UObject> CapitalSpawnStrategyClass;
	UPROPERTY()
	TScriptInterface<ISpawnStrategy> CapitalSpawnStrategy;

	UFUNCTION()
	void ReceiveOnGridGenerationStarted(int Rows, int Columns);
	UFUNCTION()
	void ReceiveOnTileGenerated(TScriptInterface<IGridPlatform> Tile, int Row, int Column);
	UFUNCTION()
	void ReceiveOnGridGenerationEnd(int Rows, int Columns);

	void AddTile(TScriptInterface<IGridPlatform> Tile, int Row, int Column) const;
	void ResizeTileMatrix(int Rows, int Columns) const;

	UGridGenerator* GetGridGenerator() const;
	UCapitalPlacementGenerator* GetCapitalPlacementGenerator() const;
};
