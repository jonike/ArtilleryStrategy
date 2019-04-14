// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Resource.generated.h"

class UTexture2D;
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
};

bool operator==(const FResource& Lhs, const FResource& Rhs);

uint32 GetTypeHash(const FResource& Resource);
