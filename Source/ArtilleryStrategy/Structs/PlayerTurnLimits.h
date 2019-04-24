// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueLimit.h"
#include "PlayerTurnLimits.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FPlayerTurnLimits
{
	GENERATED_BODY()

public:
	void ResetAllLimits();

	auto GetBuildingsLimit() const { return BuildingsLimit; }
	auto GetTilesLimit() const { return TilesLimit; }

private:
	UPROPERTY(EditAnywhere)
	FValueLimit BuildingsLimit;

	UPROPERTY(EditAnywhere)
	FValueLimit TilesLimit;
};
