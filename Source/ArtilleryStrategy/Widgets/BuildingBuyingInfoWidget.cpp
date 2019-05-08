// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBuyingInfoWidget.h"
#include "Structs/BuildingData.h"

void UBuildingBuyingInfoWidget::SetupWidget(FName RowName, FBuildingData& BuildingData)
{
	BuildingRowName = RowName;
	if (const auto IconWidget = GetIconWidget())
	{
		IconWidget->SetBrushFromTexture(BuildingData.Icon);
	}
	if (const auto NameWidget = GetNameWidget())
	{
		NameWidget->SetText(FText::FromName(BuildingData.FriendlyName));
	}
	if (const auto CostWidget = GetCostWidget())
	{
		// TODO: show building cost
		CostWidget->SetText(FText::FromString(TEXT("Not implemented!")));
	}
}

void UBuildingBuyingInfoWidget::SpawnBuilding()
{
	OnBuyClicked.Broadcast(BuildingRowName);
}
