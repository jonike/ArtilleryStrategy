// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileCoordinates.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FTileCoordinates
{
	GENERATED_BODY()

public:
	FTileCoordinates() = default;
	FTileCoordinates(int Row, int Column);

	void Init(int R, int C);
	TArray<FTileCoordinates> GetIncidentCoordinates(int TotalRows, int TotalColumns, int Distance) const;

private:
	UPROPERTY(VisibleInstanceOnly)
	int Row;

	UPROPERTY(VisibleInstanceOnly)
	int Column;

	bool IsValidValue(int Value, int Max) const;
	bool IsEqualToCurrent(int OtherRow, int OtherColumn) const;
};
