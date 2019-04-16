// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "SubclassOf.h"
#include "PlainGridPass.generated.h"

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

	AActor* SpawnPlatform(const FWorldParams& Params, const FVector& Location) const;
};
