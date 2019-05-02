// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectBuildingClass.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/Building.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ScriptInterface.h"

USelectBuildingClass::USelectBuildingClass()
{
	SelectedTile.AllowNoneAsValue(false);
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USelectBuildingClass, SelectedTile), UGridPlatform::StaticClass());
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USelectBuildingClass, SelectedTile), UCanBeOwned::StaticClass());

	BuildingClass.AllowNoneAsValue(false);
	// TODO: fix AddClassFilter() not working
	BuildingClass.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(USelectBuildingClass, BuildingClass), UBuilding::StaticClass());
	BuildingClass.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(USelectBuildingClass, BuildingClass), UCanBeOwned::StaticClass());
}

EBTNodeResult::Type USelectBuildingClass::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto TileObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelectedTile.SelectedKeyName))
	{
		if (Cast<IGridPlatform>(TileObject))
		{
			SelectClass(OwnerComp, NodeMemory, TileObject);
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type USelectBuildingClass::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void USelectBuildingClass::OnGameplayTaskActivated(UGameplayTask& Task)
{

}

void USelectBuildingClass::SelectClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IGridPlatform>& Tile)
{
	// TODO: switch on what kind of resources tile has
	SelectMineralBuildingClass(OwnerComp, NodeMemory, Tile);
}

void USelectBuildingClass::SelectMineralBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IGridPlatform>& Tile)
{
	// TODO: provide logic for selecting mineral building class
}

void USelectBuildingClass::SelectEnergyBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IGridPlatform>& Tile)
{
	// TODO: provide logic for selecting energy building class
}
