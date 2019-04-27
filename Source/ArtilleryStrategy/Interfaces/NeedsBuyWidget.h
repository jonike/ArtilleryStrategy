// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanBeOwned.h"
#include "NeedsBuyWidget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNeedsBuyWidget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API INeedsBuyWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ShowBuyWidget(TScriptInterface<ICanBeOwned> PropertyToBuy) = 0;
	virtual void HideBuyWidget() = 0;
	virtual bool IsBuyWidgetVisible() const = 0;
};
