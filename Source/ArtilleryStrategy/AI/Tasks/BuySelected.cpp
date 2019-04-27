// Fill out your copyright notice in the Description page of Project Settings.


#include "BuySelected.h"
#include "Interfaces/GridPlatform.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/CanBeOwned.h"

UBuySelected::UBuySelected()
{
	Selected.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelected, Selected), UCanBeOwned::StaticClass());
}

EBTNodeResult::Type UBuySelected::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto PlayerState = Controller->GetPlayerState<ADefaultPlayerState>();
	const auto StoredObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(Selected.SelectedKeyName);
	if (!StoredObject)
	{
		return EBTNodeResult::Failed;
	}
	const auto Tile = Cast<ICanBeOwned>(StoredObject);
	if (!Tile)
	{
		return EBTNodeResult::Failed;
	}
	if (PlayerState->GetResourceWallet()->IsEnoughPack(Tile->GetResourcesToOwn()))
	{
		const auto BuyResult = BuySelected(OwnerComp, NodeMemory, StoredObject);;
		return BuyResult;
	}
	return EBTNodeResult::Failed;
}

void UBuySelected::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UBuySelected::BuySelected(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UObject* ObjectToBuy)
{
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBuySelected::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
