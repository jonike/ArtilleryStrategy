// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanBuyCells.generated.h"

class IGridPlatform;
class ICanBeOwned;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanBuyCells : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ARTILLERYSTRATEGY_API ICanBuyCells
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ShowBuyWidget(ICanBeOwned& PropertyToBuy) = 0;
	virtual void HideBuyWidget() = 0;
	virtual bool IsBuyWidgetVisible() const = 0;
	virtual void BuyCell(ICanBeOwned& Cell) = 0;
};
