// Fill out your copyright notice in the Description page of Project Settings.

#include "ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetBlackboardComponent()->ClearValue(Key.SelectedKeyName);
	return EBTNodeResult::Succeeded;
}

void UClearValue::OnGameplayTaskActivated(UGameplayTask& Task)
{
}
