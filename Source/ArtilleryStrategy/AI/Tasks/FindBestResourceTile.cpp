// Fill out your copyright notice in the Description page of Project Settings.


#include "FindBestResourceTile.h"

EBTNodeResult::Type UFindBestResourceTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	return EBTNodeResult::Succeeded;
}

void UFindBestResourceTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UFindBestResourceTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
