// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAllWeapons.h"
#include "AI/Controllers/AdvancedAIController.h"

UFireAllWeapons::UFireAllWeapons()
{
}

EBTNodeResult::Type UFireAllWeapons::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Controller = Cast<AAdvancedAIController>(OwnerComp.GetAIOwner()))
	{
		Controller->OnFire.Broadcast();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UFireAllWeapons::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UFireAllWeapons::OnGameplayTaskActivated(UGameplayTask& Task)
{
}
