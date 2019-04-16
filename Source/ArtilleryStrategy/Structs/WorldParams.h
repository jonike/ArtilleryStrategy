// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldParams.generated.h"

class UTileMatrix;
/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FWorldParams
{
	GENERATED_BODY()

	void Initialize(UObject* Context);

	UPROPERTY(VisibleInstanceOnly)
	UTileMatrix* TileMatrix;

	UPROPERTY()
	UWorld* CurrentWorld;
};
