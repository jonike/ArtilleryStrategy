// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceBuildingsManager.generated.h"

class IResourceBuilding;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceBuildingsManager : public UObject
{
	GENERATED_BODY()
	
public:
	void GatherResources();
	void AddResourceBuilding(TScriptInterface<IResourceBuilding> Building);

private:
	TArray<TScriptInterface<IResourceBuilding>> ResourceBuildings;
};
