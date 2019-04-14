// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanBuyBuildings.generated.h"

class IBuilding;
class IGridPlatform;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanBuyBuildings : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API ICanBuyBuildings
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void CreateSelectedBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) = 0;
};
