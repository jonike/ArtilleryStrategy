// Fill out your copyright notice in the Description page of Project Settings.

#include "BuyPlatformWidget.h"
#include "Interfaces/CanBuyCells.h"
#include "Interfaces/CanBeOwned.h"

void UBuyPlatformWidget::BuyCell() const
{
	if (auto Buyer = GetBuyer())
	{
		const auto Property = PropertyToBuy.GetObject();
		check(Property);
		Buyer->BuyCell(*Cast<ICanBeOwned>(Property));
	}
}

void UBuyPlatformWidget::CloseBuyWidget() const
{
	if (auto Buyer = GetBuyer())
	{
		Buyer->HideBuyWidget();
	}
}

void UBuyPlatformWidget::SetPropertyToBuy(ICanBeOwned& Property)
{
	PropertyToBuy = Cast<UObject>(&Property);
}

ICanBuyCells* UBuyPlatformWidget::GetBuyer() const
{
	if (const auto PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (const auto ControllerCanBuy = Cast<ICanBuyCells>(PlayerController))
		{
			return ControllerCanBuy;
		}
	}
	return nullptr;
}
