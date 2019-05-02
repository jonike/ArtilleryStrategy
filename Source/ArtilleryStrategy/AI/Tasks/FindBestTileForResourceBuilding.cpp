// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBestTileForResourceBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/PlayerProperty.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Game/States/DefaultGS.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Engine/World.h"
#include "Structs/WorldParams.h"
#include "Components/WorldGenerator.h"
#include "Objects/TileMatrix.h"
#include "Interfaces/OwnerController.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindBestTileForResourceBuilding::UFindBestTileForResourceBuilding()
{
	ResultTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBestTileForResourceBuilding, ResultTile), UGridPlatform::StaticClass());
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

EBTNodeResult::Type UFindBestTileForResourceBuilding::GetBestResourceTile(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const FWorldParams& Params)
{
	const auto SelfOwner = OwnerComp.GetAIOwner();
	for (auto Row = 0; Row < Params.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.GetColumns(); ++Column)
		{
			const auto Tile = Params.TileMatrix->Get(Row, Column).GetObject();
			if (const auto OwnedTile = Cast<IPlayerProperty>(Tile))
			{
				const auto TileOwner = OwnedTile->GetOwnerController().GetObject();
				if (TileOwner == SelfOwner)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ResultTile.SelectedKeyName, Tile);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
