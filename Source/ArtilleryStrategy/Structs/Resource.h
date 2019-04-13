// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditor/Private/SRowEditor.h"
#include "Resource.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResource : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FriendlyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MinAmountSpawned = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxAmountSpawned = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseCost = 10.0;

	bool IsSameResource(const FResource& Resource) const { return FriendlyName == Resource.FriendlyName; }
};

inline bool operator==(const FResource& Lhs, const FResource& Rhs)
{
	return Lhs.Icon == Rhs.Icon
			&& Lhs.FriendlyName == Rhs.FriendlyName
			&& Lhs.MinAmountSpawned == Rhs.MinAmountSpawned
			&& Lhs.MaxAmountSpawned == Rhs.MaxAmountSpawned
			&& Lhs.BaseCost == Rhs.BaseCost;
}

inline uint32 GetTypeHash(const FResource& Resource)
{
	return GetTypeHash(Resource.FriendlyName);
}
