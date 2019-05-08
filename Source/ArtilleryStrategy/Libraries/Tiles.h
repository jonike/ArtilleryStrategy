// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tiles.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UTiles : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static TSet<UObject*> FilterOnlyTilesWithoutBuildings(const TSet<UObject*>& Tiles);
};
