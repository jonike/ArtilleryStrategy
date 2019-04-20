// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "RandomBumpPass.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API URandomBumpPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	virtual TPair<int, int> GetRandomIndexes(const FWorldParams& Params) const;
	virtual void AddBumpInPosition(FWorldParams& Params, int CenterRow, int CenterColumn) const;

private:
	UPROPERTY(Category = "Bumps",EditAnywhere)
	int BumpAmount = 3;

	UPROPERTY(Category = "Bumps", EditAnywhere)
	TArray<int> BumpOffsets{3, 2, 1, 1};

	void ApplyOffset(FWorldParams& Params, int Row, int Column, int Offset) const;
};
