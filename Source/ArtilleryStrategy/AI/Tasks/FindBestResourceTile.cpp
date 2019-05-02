// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBestResourceTile.h"
#include "Engine/World.h"
#include "Game/States/DefaultGS.h"
#include "Components/WorldGenerator.h"
#include "Interfaces/GridPlatform.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Objects/TileMatrix.h"

UFindBestResourceTile::UFindBestResourceTile()
{
	bNotifyTick = false;
	bNotifyTaskFinished = false;
	Key.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBestResourceTile, Key), UGridPlatform::StaticClass());
}

EBTNodeResult::Type UFindBestResourceTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO: rewrite to find best tile
	const auto GameState = GetWorld()->GetGameState<ADefaultGS>();
	check(GameState);
	const auto& Params = GameState->GetWorldGenerator()->GetWorldParams();
	const auto Row = FMath::RandRange(0, Params.GetRows() - 1);
	const auto Column = FMath::RandRange(0, Params.GetColumns() - 1);
	const auto Tile = Params.GetTileMatrix()->Get(Row, Column);
	OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(Key.SelectedKeyName, Tile.GetObject());
	return EBTNodeResult::Succeeded;
}

void UFindBestResourceTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UFindBestResourceTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
