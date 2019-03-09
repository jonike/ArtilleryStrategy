// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingSelectorWidget.h"
#include "UniformGridPanel.h"
#include "Engine/DataTable.h"

void UBuildingSelectorWidget::FillBuildingsData(UUniformGridPanel* GridPanel)
{
	check(GridPanel);
	for (auto RowName : BuildingsDataTable->GetRowNames())
	{
		AddGridItemWidget(RowName);
	}
}

void UBuildingSelectorWidget::AddGridItemWidget(FName RowName)
{
	// TODO: create or get from cache grid item widget
}
