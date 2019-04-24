// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "SubclassOf.h"
#include "TileSpawnPass.generated.h"

class AActor;
/**
 * 
 */
UCLASS(BlueprintType)
class ARTILLERYSTRATEGY_API UPlainGridPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

private:
	UPROPERTY(Category = "Spacing", EditAnywhere)
	float RowSpacing = 100.f;

	UPROPERTY(Category = "Spacing", EditAnywhere)
	float ColumnSpacing = 100.f;

	UPROPERTY(Category = "Spacing", EditAnywhere)
	float HeightSpacing = 100.f;

	UPROPERTY(Category = "Location", EditAnywhere)
	FVector OriginOffset;

	UPROPERTY(EditAnywhere, Category = Generation, meta = (MustImplement = "GridPlatform"))
	TSubclassOf<AActor> GridPlatformClass;

	void GenerateGrid(FWorldParams& Params, int Rows, int Columns) const;
	void ResizeTilesMatrix(FWorldParams& Params, int& Rows, int& Columns);
	
	FVector CalculateStartLocation(int Rows, int Columns) const;
	AActor* SpawnPlatform(const FWorldParams& Params, const FVector& Location) const;
};
