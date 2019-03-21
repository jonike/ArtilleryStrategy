// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"
#include "UserWidget.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Widgets/BuildingSelectorWidget.h"
#include "Interfaces/CanBuyCells.h"
#include "Player/Controllers/DefaultPlayerController.h"

void ADefaultHUD::ShowBuyCellWidget(ICanBeOwned& Property)
{
	HideBuyWidget();
	if (!BuyCellWidget)
	{
		CreateBuyCellWidget();
	}
	BuyCellWidget->SetPropertyToBuy(Property);
	BuyCellWidget->AddToViewport();
}

void ADefaultHUD::ShowBuildingSelectorWidget()
{
	HideBuyWidget();
	if (!BuildingSelectorWidget)
	{
		CreateBuildingSelectorWidget();
	}
	BuildingSelectorWidget->AddToViewport();
}

void ADefaultHUD::HideBuyWidget()
{
	if (ActiveBuyWidget)
	{
		ActiveBuyWidget->RemoveFromViewport();
	}
}

bool ADefaultHUD::IsBuyWidgetsVisible() const
{
	return ActiveBuyWidget != nullptr;
}

void ADefaultHUD::WhenBuyClicked(TScriptInterface<ICanBeOwned> Property)
{
	if (IsBuyCellWidgetActive())
	{
		check(Property.GetInterface());
		auto& Buyer = GetBuyer();
		// TODO: pass TScriptInterface instead
		Buyer.BuyCell(*Cast<ICanBeOwned>(Property.GetObject()));
	}
	if (bAutoCloseBuyWidget)
	{
		HideBuyWidget();
	}
}

void ADefaultHUD::WhenCloseClicked()
{
	HideBuyWidget();
}

void ADefaultHUD::CreateBuyCellWidget()
{
	BuyCellWidget = CreateWidget<UBuyPlatformWidget>(GetOwningPlayerController(), BuyCellWidgetClass);
	check(BuyCellWidget);
	BuyCellWidget->OnBuyClicked.AddDynamic(this, &ADefaultHUD::WhenBuyClicked);
	BuyCellWidget->OnCloseClicked.AddDynamic(this, &ADefaultHUD::WhenCloseClicked);
}

void ADefaultHUD::CreateBuildingSelectorWidget()
{
	BuildingSelectorWidget = CreateWidget<UBuildingSelectorWidget>(GetOwningPlayerController(), BuildingsSelectorWidgetClass);
	check(BuildingSelectorWidget);
}

bool ADefaultHUD::IsBuyCellWidgetActive() const
{
	return ActiveBuyWidget == BuyCellWidget;
}

ICanBuyCells& ADefaultHUD::GetBuyer() const
{
	const auto Controller = GetOwningPlayerController();
	const auto Buyer = Cast<ICanBuyCells>(Controller);
	check(Buyer);
	return *Buyer;
}
