// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefaultGS.generated.h"

class IMapGenerator;
class UResourceDepositGenerator;
class ISpawnStrategy;
class UCapitalPlacementGenerator;
class UGridGenerator;
class UTileMatrix;
class IGridPlatform;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultGS : public AGameStateBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGridGenerationEndedSignature, UTileMatrix*, Tiles);

public:
	ADefaultGS();

	FOnGridGenerationEndedSignature OnGridGenerationEnded;

protected:
	void PostInitializeComponents() override;

private:
	UPROPERTY(Category = "Tiles", VisibleAnywhere)
	UTileMatrix* Matrix;

	UPROPERTY(Category = "Generation", EditAnywhere)
	UGridGenerator* GridGenerator;

	UPROPERTY(Category = "Generation", EditAnywhere)
	UCapitalPlacementGenerator* CapitalPlacementGenerator;

	UPROPERTY(Category = "Generation", EditAnywhere)
	UResourceDepositGenerator* ResourceDepositGenerator;

	UFUNCTION()
	void ReceiveOnGridGenerationStarted(int Rows, int Columns);
	UFUNCTION()
	void ReceiveOnTileGenerated(TScriptInterface<IGridPlatform> Tile, int Row, int Column);
	UFUNCTION()
	void ReceiveOnGridGenerationEnd(int Rows, int Columns);

	void AddTile(TScriptInterface<IGridPlatform> Tile, int Row, int Column) const;
	void ResizeTileMatrix(int Rows, int Columns) const;

	UGridGenerator* GetGridGenerator() const;
};
