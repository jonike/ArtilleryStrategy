// Fill out your copyright notice in the Description page of Project Settings.

#include "BuyPlatformWidget.h"
#include "CanBuyCells.h"

void UBuyPlatformWidget::BuyCell() const
{
	if (auto Buyer = GetBuyer())
	{
		// TODO: pass actual pointer to cell; nullptr should trigger check()
		Buyer->BuyCell(nullptr);
	}
}

void UBuyPlatformWidget::CloseBuyWidget() const
{
	if (auto Buyer = GetBuyer())
	{
		Buyer->HideBuyWidget();
	}
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
