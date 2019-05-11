// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBestResourceTile.h"
#include "Engine/World.h"
#include "Game/States/DefaultGS.h"
#include "Interfaces/WorldTile.h"
#include "AI/Controllers/AdvancedAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/ExpansionPreferences.h"

UFindBestResourceTile::UFindBestResourceTile()
{
	bNotifyTick = false;
	bNotifyTaskFinished = false;
	ResultKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFindBestResourceTile, ResultKey), UWorldTile::StaticClass());
}

EBTNodeResult::Type UFindBestResourceTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO: rewrite to find best tile
	const auto Controller = OwnerComp.GetAIOwner();
	if (const auto AdvancedController = Cast<AAdvancedAIController>(Controller))
	{
		const auto& Preferences = AdvancedController->GetExpansionPreferences();
		const auto TileData = Preferences->GetBest();
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ResultKey.SelectedKeyName, TileData.Tile.GetObject());
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

void UFindBestResourceTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UFindBestResourceTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
