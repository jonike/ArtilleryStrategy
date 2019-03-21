// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSelectorWidget.h"
#include "UniformGridPanel.h"
#include "UniformGridSlot.h"
#include "Engine/DataTable.h"
#include "Interfaces/BuildingGridItemWidget.h"
#include "Structs/BuildingData.h"

void UBuildingSelectorWidget::FillBuildingsData(UUniformGridPanel* GridPanel)
{
	check(GridPanel);
	auto Names = BuildingsDataTable->GetRowNames();
	for (auto i = 0; i < Names.Num(); ++i)
	{
		AddGridItemWidget(Names[i], i, *GridPanel);
	}
}

void UBuildingSelectorWidget::AddGridItemWidget(const FName RowName, const int Number, UUniformGridPanel& GridPanel)
{
	auto GridItemWidget = LoadOrCreateGridItem(Number);
	const auto BuildingData = BuildingsDataTable->FindRow<FBuildingData>(RowName, TEXT("Get row data for filling building selector widget"));

	// There always should be correct row with given name
	check(BuildingData);
	GridItemWidget->Setup(*BuildingData);
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
	check(NewWidget);
	GridItemWidgets.Add(NewWidget);
	return NewWidget;
}
