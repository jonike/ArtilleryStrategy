// Fill out your copyright notice in the Description page of Project Settings.


#include "FindCapitalTile.h"
#include "Interfaces/WorldTile.h"
#include "Interfaces/PlayerProperty.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindCapitalTile::UFindCapitalTile()
{
	CapitalTileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindCapitalTile, CapitalTileKey), UWorldTile::StaticClass());
	CapitalTileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindCapitalTile, CapitalTileKey), UPlayerProperty::StaticClass());
}

EBTNodeResult::Type UFindCapitalTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto PlayerState = OwnerComp.GetAIOwner()->GetPlayerState<ADefaultPlayerState>())
	{
		if (const auto CapitalTile = PlayerState->GetOwnedTiles().CreateConstIterator())
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(CapitalTileKey.SelectedKeyName, *CapitalTile);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

void UFindCapitalTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}
