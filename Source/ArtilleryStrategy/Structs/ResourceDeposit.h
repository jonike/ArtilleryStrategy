// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceAmount.h"
#include "ResourceDeposit.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct ARTILLERYSTRATEGY_API FResourceDeposit
{
	GENERATED_BODY()

	UPROPERTY(Category = "Resource", EditAnywhere)
	FResourceAmount ResourceAmount;
};

inline bool operator==(const FResourceDeposit& Lhs, const FResourceDeposit& Rhs)
{
	return Lhs.ResourceAmount == Rhs.ResourceAmount;
}

inline uint32 GetTypeHash(const FResourceDeposit& ResourceDeposit)
{
	return GetTypeHash(ResourceDeposit.ResourceAmount);
}
