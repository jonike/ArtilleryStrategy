// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/LandscapeGenerationStrategy.h"
#include "SubclassOf.h"
#include "PlainGridGenerator.generated.h"

class AActor;
/**
 * 
 */
UCLASS(BlueprintType)
class ARTILLERYSTRATEGY_API UPlainGridGenerator : public UDataAsset, public ILandscapeGenerationStrategy
{
	GENERATED_BODY()

public:
	void Generate(const FLandscapeGenerationParams& Params) override;

private:
	UPROPERTY(Category = "Params", EditAnywhere)
	int Rows = 0;

	UPROPERTY(Category = "Params", EditAnywhere)
	int Columns = 0;

	UPROPERTY(Category = "Params", EditAnywhere)
	float RowSpacing = 100.f;

	UPROPERTY(Category = "Params", EditAnywhere)
	float ColumnSpacing = 100.f;

	UPROPERTY(Category = "Params", EditAnywhere)
	FVector OriginOffset;

	UPROPERTY(EditAnywhere, Category = Generation, meta = (MustImplement = "GridPlatform"))
	TSubclassOf<AActor> GridPlatformClass;

	AActor* SpawnPlatform(const FVector& Location) const;
};
