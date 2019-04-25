// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"
#include "UserWidget.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Widgets/BuildingSelectorWidget.h"
#include "Interfaces/CanBuyCells.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Widgets/ResourceStorageWidget.h"
#include "Widgets/TurnWidget.h"
#include "Widgets/PlayerTurnLimitsWidget.h"

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

void ADefaultHUD::BeginPlay()
{
	TurnWidget = CreateWidget<UTurnWidget>(GetOwningPlayerController(), TurnWidgetClass);
	TurnWidget->AddToViewport();
	PlayerTurnLimitsWidget = CreateWidget<UPlayerTurnLimitsWidget>(GetOwningPlayerController(), PlayerTurnLimitsWidgetClass);
	PlayerTurnLimitsWidget->AddToViewport();
	ShowResourceStorageWidget();
}

void ADefaultHUD::ReceiveOnBuyCellClicked(TScriptInterface<ICanBeOwned> Property)
{
	check(Property.GetInterface());
	auto Buyer = GetCellBuyer();
	Buyer->BuyCell(Property);

	if (bAutoCloseBuyWidget)
	{
		HideBuyWidget();
	}
}

void ADefaultHUD::ReceiveOnBuyBuildingClicked(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass)
{
	const auto Buyer = GetBuildingsBuyer();
	Buyer->CreateSelectedBuilding(Cell, BuildingClass);

	if (bAutoCloseBuyWidget)
	{
		HideBuyWidget();
	}
}

void ADefaultHUD::ReceiveOnCloseClicked()
{
	HideBuyWidget();
}

void ADefaultHUD::ShowResourceStorageWidget()
{
	if (!ResourceStorageWidget)
	{
		CreateResourceStorageWidget();
	}
	if (!IsResourceStorageWidgetVisible())
	{
		ResourceStorageWidget->AddToViewport();
	}
}

void ADefaultHUD::HideResourceStorageWidget()
{
	if (IsResourceStorageWidgetVisible())
	{
		ResourceStorageWidget->RemoveFromViewport();
	}
}

bool ADefaultHUD::IsResourceStorageWidgetVisible() const
{
	return ResourceStorageWidget && ResourceStorageWidget->IsInViewport();
}

void ADefaultHUD::CreateBuyCellWidget()
{
	BuyCellWidget = CreateWidget<UBuyPlatformWidget>(GetOwningPlayerController(), BuyCellWidgetClass);
	check(BuyCellWidget);
	BuyCellWidget->OnBuyClicked.AddDynamic(this, &ADefaultHUD::ReceiveOnBuyCellClicked);
	BuyCellWidget->OnCloseClicked.AddDynamic(this, &ADefaultHUD::ReceiveOnCloseClicked);
}

void ADefaultHUD::CreateBuildingSelectorWidget()
{
	BuildingSelectorWidget = CreateWidget<UBuildingSelectorWidget>(GetOwningPlayerController(),
																	BuildingsSelectorWidgetClass);
	check(BuildingSelectorWidget);
	BuildingSelectorWidget->OnCloseClicked.AddDynamic(this, &ADefaultHUD::ReceiveOnCloseClicked);
	BuildingSelectorWidget->OnBuyClicked.AddDynamic(this, &ADefaultHUD::ReceiveOnBuyBuildingClicked);
}

void ADefaultHUD::CreateResourceStorageWidget()
{
	ResourceStorageWidget = CreateWidget<UResourceStorageWidget>(GetOwningPlayerController(), ResourceStorageWidgetClass);
	check(ResourceStorageWidget);
}

TScriptInterface<ICanBuyCells> ADefaultHUD::GetCellBuyer() const
{
	return GetOwningPlayerController();
}

TScriptInterface<ICanBuyBuildings> ADefaultHUD::GetBuildingsBuyer() const
{
	return GetOwningPlayerController();
}
