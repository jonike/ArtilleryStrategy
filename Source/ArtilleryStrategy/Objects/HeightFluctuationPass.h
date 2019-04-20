// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "HeightFluctuationPass.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UHeightFluctuationPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	bool IsFluctuationOccured() const;

private:
	UPROPERTY(EditAnywhere)
	float FluctuationChance = 0.05f;

	UPROPERTY(EditAnywhere)
	int FluctuationDirection = 1;
};
