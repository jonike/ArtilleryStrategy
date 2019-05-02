// Fill out your copyright notice in the Description page of Project Settings.

#include "BuyPlatformWidget.h"
#include "Interfaces/PlayerProperty.h"

void UBuyPlatformWidget::BuyCell() const
{
	OnBuyClicked.Broadcast(PropertyToBuy);
}

void UBuyPlatformWidget::CloseBuyWidget() const
{
	OnCloseClicked.Broadcast();
}

void UBuyPlatformWidget::SetPropertyToBuy(TScriptInterface<IPlayerProperty> Property)
{
	PropertyToBuy = Property;
}
