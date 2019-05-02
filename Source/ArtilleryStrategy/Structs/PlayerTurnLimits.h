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

	FValueLimit& GetBuildingsLimit() { return BuildingsLimit; }
	FValueLimit& GetTilesLimit() { return TilesLimit; }

	const FValueLimit& GetBuildingsLimit() const { return BuildingsLimit; }
	const FValueLimit& GetTilesLimit() const { return TilesLimit; }

private:
	UPROPERTY(EditAnywhere)
	FValueLimit BuildingsLimit;

	UPROPERTY(EditAnywhere)
	FValueLimit TilesLimit;
};
