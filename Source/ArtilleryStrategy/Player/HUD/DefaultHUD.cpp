// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"
#include "UserWidget.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Widgets/BuildingSelectorWidget.h"
#include "Interfaces/CanBuyCells.h"
#include "Player/Controllers/DefaultPlayerController.h"

void ADefaultHUD::ShowBuyCellWidget(TScriptInterface<ICanBeOwned> Property)
{
	HideBuyWidget();
	if (!BuyCellWidget)
	{
		CreateBuyCellWidget();
	}
	BuyCellWidget->SetPropertyToBuy(Property);
	BuyCellWidget->AddToViewport();
	ActiveBuyWidget = BuyCellWidget;
}

void ADefaultHUD::ShowBuildingSelectorWidget(TScriptInterface<IGridPlatform> Cell)
{
	HideBuyWidget();
	if (!BuildingSelectorWidget)
	{
		CreateBuildingSelectorWidget();
	}
	BuildingSelectorWidget->SetSelectedPlatform(Cell);
	BuildingSelectorWidget->AddToViewport();
	ActiveBuyWidget = BuildingSelectorWidget;
}

void ADefaultHUD::HideBuyWidget()
{
	if (ActiveBuyWidget)
	{
		ActiveBuyWidget->RemoveFromViewport();
		ActiveBuyWidget = nullptr;
	}
}

bool ADefaultHUD::IsBuyWidgetsVisible() const
{
	return ActiveBuyWidget != nullptr;
}

void ADefaultHUD::WhenBuyCellClicked(TScriptInterface<ICanBeOwned> Property)
{
	check(Property.GetInterface());
	auto Buyer = GetCellBuyer();
	Buyer->BuyCell(Property);

	if (bAutoCloseBuyWidget)
	{
		HideBuyWidget();
	}
}

void ADefaultHUD::WhenBuyBuildingClicked(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass)
{
	const auto Buyer = GetBuildingsBuyer();
	Buyer->BuyBuilding(Cell, BuildingClass);

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
	BuyCellWidget->OnBuyClicked.AddDynamic(this, &ADefaultHUD::WhenBuyCellClicked);
	BuyCellWidget->OnCloseClicked.AddDynamic(this, &ADefaultHUD::WhenCloseClicked);
}

void ADefaultHUD::CreateBuildingSelectorWidget()
{
	BuildingSelectorWidget = CreateWidget<UBuildingSelectorWidget>(GetOwningPlayerController(),
																	BuildingsSelectorWidgetClass);
	check(BuildingSelectorWidget);
	BuildingSelectorWidget->OnCloseClicked.AddDynamic(this, &ADefaultHUD::WhenCloseClicked);
	BuildingSelectorWidget->OnBuyClicked.AddDynamic(this, &ADefaultHUD::WhenBuyBuildingClicked);
}

TScriptInterface<ICanBuyCells> ADefaultHUD::GetCellBuyer() const
{
	return GetOwningPlayerController();
}

TScriptInterface<ICanBuyBuildings> ADefaultHUD::GetBuildingsBuyer() const
{
	return GetOwningPlayerController();
}
