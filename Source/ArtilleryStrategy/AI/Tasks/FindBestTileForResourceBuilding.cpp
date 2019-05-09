// Fill out your copyright notice in the Description page of Project Settings.

#include "FindBestTileForResourceBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Interfaces/PlayerProperty.h"
#include "AIController.h"
#include "Game/States/DefaultGS.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Engine/World.h"
#include "Structs/WorldParams.h"
#include "Components/WorldGenerator.h"
#include "Interfaces/OwnerState.h"
#include "GameFramework/PlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Libraries/Tiles.h"

UFindBestTileForResourceBuilding::UFindBestTileForResourceBuilding()
{
	ResultTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBestTileForResourceBuilding, ResultTile), UWorldTile::StaticClass());
	ResultTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBestTileForResourceBuilding, ResultTile), UPlayerProperty::StaticClass());
}

EBTNodeResult::Type UFindBestTileForResourceBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto GameState = OwnerComp.GetWorld()->GetGameState<ADefaultGS>())
	{
		const auto& WorldParams = GameState->GetWorldGenerator()->GetWorldParams();
		return GetBestResourceTile(OwnerComp, NodeMemory, WorldParams);
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UFindBestTileForResourceBuilding::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Failed;
}

void UFindBestTileForResourceBuilding::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UFindBestTileForResourceBuilding::GetBestResourceTile(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const FWorldParams& Params) const
{
	const auto SelfOwner = OwnerComp.GetAIOwner();
	if (const auto OwnerState = SelfOwner->GetPlayerState<IOwnerState>())
	{
		const auto TilesForBuilding = OwnerState->GetOwnedTiles();
		const auto TilesWithoutBuildings = UTiles::FilterOnlyTilesWithoutBuildings(TilesForBuilding);
		if (TilesWithoutBuildings.Num() > 0)
		for (const auto& TileObject : TilesWithoutBuildings)
		{
			if (const auto Tile = Cast<IWorldTile>(TileObject))
			{
				if (Tile->GetResourceDeposits().Num() > 0)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ResultTile.SelectedKeyName, TileObject);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
