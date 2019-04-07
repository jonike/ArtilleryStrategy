// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Resource.h"
#include "ResourceAmount.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourceAmount
{
	GENERATED_BODY()

	UPROPERTY(Category = "Resource", EditAnywhere, BlueprintReadWrite)
	FResource Resource;

	UPROPERTY(Category = "Resource", EditAnywhere, BlueprintReadWrite)
	float Amount;
};

inline bool operator==(const FResourceAmount& Lhs, const FResourceAmount& Rhs)
{
	return Lhs.Amount == Rhs.Amount && Lhs.Resource == Rhs.Resource;
}
