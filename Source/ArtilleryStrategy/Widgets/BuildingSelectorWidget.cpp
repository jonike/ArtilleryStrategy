// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSelectorWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "Engine/DataTable.h"
#include "Interfaces/BuildingGridItemWidget.h"
#include "Structs/BuildingData.h"
#include "BuildingBuyingInfoWidget.h"

void UBuildingSelectorWidget::SetSelectedPlatform(const TScriptInterface<IWorldTile> Selected)
{
	SelectedPlatform = Selected;
}

void UBuildingSelectorWidget::FillBuildingsData(UUniformGridPanel* GridPanel)
{
	check(GridPanel);
	auto Names = BuildingsDataTable->GetRowNames();
	for (auto i = 0; i < Names.Num(); ++i)
	{
		AddItemWidget(Names[i], i, GridPanel);
	}
}

void UBuildingSelectorWidget::CloseWidget() const
{
	OnCloseClicked.Broadcast();
}

void UBuildingSelectorWidget::ReceiveOnBuyClicked(FName BuildingName)
{
	const auto Building = BuildingsDataTable->FindRow<FBuildingData>(BuildingName, TEXT("Getting building data for spawning"));
	check(Building);
	OnBuyClicked.Broadcast(SelectedPlatform, Building->SpawnClass);
}

void UBuildingSelectorWidget::SetPositionInGrid(UUserWidget* const ItemWidget, const int Number)
{
	const auto ItemWidgetSlot = Cast<UUniformGridSlot>(ItemWidget->Slot);
	check(ItemWidgetSlot);
	ItemWidgetSlot->SetRow(Number / GridColumns);
	ItemWidgetSlot->SetColumn(Number % GridColumns);
}

void UBuildingSelectorWidget::AddWidgetToGrid(const TScriptInterface<IBuildingGridItemWidget> GridItemWidget, UUniformGridPanel* GridPanel, const int Number)
{
	const auto ItemWidget = Cast<UUserWidget>(GridItemWidget.GetObject());
	check(ItemWidget);
	GridPanel->AddChildToUniformGrid(ItemWidget);
	SetPositionInGrid(ItemWidget, Number);
}

void UBuildingSelectorWidget::AddItemWidget(const FName RowName, const int Number, UUniformGridPanel* GridPanel)
{
	auto GridItemWidget = LoadOrCreateGridItem(Number);
	const auto BuildingData = BuildingsDataTable->FindRow<FBuildingData>(RowName, TEXT("Get row data for filling building selector widget"));
	GridItemWidget->SetupWidget(RowName, *BuildingData);
	AddWidgetToGrid(GridItemWidget, GridPanel, Number);
}

TScriptInterface<IBuildingGridItemWidget> UBuildingSelectorWidget::LoadOrCreateGridItem(const int Index)
{
	if (Index < GridItemWidgets.Num())
	{
		return GridItemWidgets[Index];
	}
	const auto NewWidget = CreateWidget(GetWorld()->GetFirstPlayerController(), GridItemWidgetClass);
	if (auto BuildingBuyingInfo = Cast<UBuildingBuyingInfoWidget>(NewWidget))
	{
		BuildingBuyingInfo->OnBuyClicked.AddDynamic(this, &UBuildingSelectorWidget::ReceiveOnBuyClicked);
	}
	check(NewWidget);
	GridItemWidgets.Add(NewWidget);
	return NewWidget;
}
