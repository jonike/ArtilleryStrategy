// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Resource.h"
#include "Structs/ResourceHandle.h"
#include "ResourceAmount.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourceAmount
{
	GENERATED_BODY()

	UPROPERTY(Category = "Resource", EditAnywhere, BlueprintReadWrite)
	FResourceHandle ResourceHandle;

	UPROPERTY(Category = "Resource", EditAnywhere, BlueprintReadWrite)
	float Amount;

	const FResource& GetResource(const FString& Context) const;
	const FResource& GetResource(const TCHAR* Context) const;
};

bool operator==(const FResourceAmount& Lhs, const FResourceAmount& Rhs);

uint32 GetTypeHash(const FResourceAmount& ResourceAmount);
