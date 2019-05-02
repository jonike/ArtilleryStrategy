// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "PlayerProperty.h"
#include "NeedsBuyWidget.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNeedsBuyWidget : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Represents class that needs to show buy widget before buying. Example: every player controller
 */
class ARTILLERYSTRATEGY_API INeedsBuyWidget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * \brief Shows buy widget when player selects some property
	 * \param PropertyToBuy property that player has selected
	 */
	virtual void ShowBuyWidget(TScriptInterface<IPlayerProperty> PropertyToBuy) = 0;

	virtual void HideBuyWidget() = 0;

	virtual bool IsBuyWidgetVisible() const = 0;
};
