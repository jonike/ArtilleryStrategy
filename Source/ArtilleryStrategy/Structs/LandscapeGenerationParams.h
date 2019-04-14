// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandscapeGenerationParams.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FLandscapeGenerationParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Rows = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Columns = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RowSpacing = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ColumnSpacing = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector OriginOffset;
};
