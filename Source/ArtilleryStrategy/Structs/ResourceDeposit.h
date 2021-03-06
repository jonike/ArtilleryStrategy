// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ResourceAmount.h"
#include "ResourceDeposit.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct ARTILLERYSTRATEGY_API FResourceDeposit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FResourceAmount ResourceAmount;
};

bool operator==(const FResourceDeposit& Lhs, const FResourceDeposit& Rhs);

uint32 GetTypeHash(const FResourceDeposit& ResourceDeposit);
