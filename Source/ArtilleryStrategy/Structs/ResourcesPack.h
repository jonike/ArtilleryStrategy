// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/ResourceAmount.h"
#include "ResourcesPack.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourcesPack
{
	GENERATED_BODY()

	UPROPERTY(Category = "Resources", EditAnywhere)
	TSet<FResourceAmount> Resources;
};
