// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LandscapeGenerationParams.generated.h"

class UTileMatrix;
/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FLandscapeGenerationParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTileMatrix* TileMatrix;
};
