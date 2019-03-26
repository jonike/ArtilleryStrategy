// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSelectorWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "Engine/DataTable.h"
#include "Interfaces/BuildingGridItemWidget.h"
#include "Structs/BuildingData.h"
#include "BuildingBuyingInfoWidget.h"

void UBuildingSelectorWidget::SetSelectedPlatform(const TScriptInterface<IGridPlatform> Selected)
{
	SelectedPlatform = Selected;
}

void UBuildingSelectorWidget::FillBuildingsData(UUniformGridPanel* GridPanel)
{
	check(GridPanel);
	auto Names = BuildingsDataTable->GetRowNames();
	for (auto i = 0; i < Names.Num(); ++i)
	{
		AddGridItemWidget(Names[i], i, *GridPanel);
	}
}

void UBuildingSelectorWidget::CloseWidget() const
{
	OnCloseClicked.Broadcast();
}

void UBuildingSelectorWidget::WhenBuyClicked(FName BuildingName)
{
	const auto Building = BuildingsDataTable->FindRow<FBuildingData>(BuildingName, TEXT("Getting building data for spawning"));
	check(Building);
	OnBuyClicked.Broadcast(SelectedPlatform, Building->SpawnClass);

}

void UBuildingSelectorWidget::AddGridItemWidget(const FName RowName, const int Number, UUniformGridPanel& GridPanel)
{
	// TODO: refactor code to eliminate casts
	// TODO: extract methods to reduce method size
	auto GridItemWidget = LoadOrCreateGridItem(Number);
	const auto BuildingData = BuildingsDataTable->FindRow<FBuildingData>(RowName, TEXT("Get row data for filling building selector widget"));
	GridItemWidget->SetupWidget(RowName, *BuildingData);
	const auto ItemWidget = Cast<UUserWidget>(GridItemWidget.GetObject());
	check(ItemWidget);
	GridPanel.AddChildToUniformGrid(ItemWidget);
	const auto ItemWidgetSlot = Cast<UUniformGridSlot>(ItemWidget->Slot);
	check(ItemWidgetSlot);
	ItemWidgetSlot->SetRow(Number / GridColumns);
	ItemWidgetSlot->SetColumn(Number % GridColumns);
	
}

TScriptInterface<IBuildingGridItemWidget> UBuildingSelectorWidget::LoadOrCreateGridItem(const int i)
{
	if (i < GridItemWidgets.Num())
	{
		return GridItemWidgets[i];
	}
	const auto NewWidget = CreateWidget(GetWorld()->GetFirstPlayerController(), GridItemWidgetClass);
	if (auto BuildingBuyingInfo = Cast<UBuildingBuyingInfoWidget>(NewWidget))
	{
		BuildingBuyingInfo->OnBuyClicked.AddDynamic(this, &UBuildingSelectorWidget::WhenBuyClicked);
	}
	check(NewWidget);
	GridItemWidgets.Add(NewWidget);
	return NewWidget;
}
