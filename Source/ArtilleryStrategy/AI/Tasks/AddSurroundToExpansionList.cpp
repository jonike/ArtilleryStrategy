// Fill out your copyright notice in the Description page of Project Settings.

#include "AddSurroundToExpansionList.h"
#include "Interfaces/WorldTile.h"
#include "Interfaces/PlayerProperty.h"
#include "AI/Controllers/AdvancedAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Structs/TileData.h"
#include "Objects/ExpansionPreferences.h"

UAddSurroundToExpansionList::UAddSurroundToExpansionList()
{
	TileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UAddSurroundToExpansionList, TileKey), UWorldTile::StaticClass());
	TileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UAddSurroundToExpansionList, TileKey), UPlayerProperty::StaticClass());
}

EBTNodeResult::Type UAddSurroundToExpansionList::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Tile = UnpackTile(OwnerComp))
	{
		if (const auto Preferences = GetExpansionPreferences(OwnerComp))
		{
			const auto Neighbors = Tile->GetTileData().GetAdjacentTiles(this);
			for (const auto& NeighborTile : Neighbors)
			{
				if (CheckIfNeedsToAdd(OwnerComp, NeighborTile))
				{
					Preferences->AddTile(NeighborTile);
				}
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UAddSurroundToExpansionList::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UAddSurroundToExpansionList::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

UExpansionPreferences* UAddSurroundToExpansionList::GetExpansionPreferences(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (const auto AdvancedController = Cast<AAdvancedAIController>(Controller))
	{
		return AdvancedController->GetExpansionPreferences();
	}
	checkNoEntry();
	return nullptr;
}

TScriptInterface<IWorldTile> UAddSurroundToExpansionList::UnpackTile(UBehaviorTreeComponent& OwnerComp) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsObject(TileKey.SelectedKeyName);
}

bool UAddSurroundToExpansionList::CheckIfNeedsToAdd(UBehaviorTreeComponent& OwnerComp, const TScriptInterface<IWorldTile> Tile) const
{
	if (const auto Property = Cast<IPlayerProperty>(Tile.GetObject()))
	{
		return !Property->HasOwnerController();
	}
	checkNoEntry();
	return false;
}
