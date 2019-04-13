// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/ResourceAmount.h"
#include "ResourcePack.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourcePack
{
	GENERATED_BODY()

	UPROPERTY(Category = "Resources", EditAnywhere)
	TSet<FResourceAmount> Resources;

	/** Compares TSet of FResourceAmount of two FResourcePack objects */
	bool ContainsEqualResourcePack(const FResourcePack& Other) const;
};
