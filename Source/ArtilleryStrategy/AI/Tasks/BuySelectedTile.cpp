// Fill out your copyright notice in the Description page of Project Settings.


#include "BuySelectedTile.h"
#include "Interfaces/GridPlatform.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/CanBeOwned.h"

UBuySelectedTile::UBuySelectedTile()
{
	Selected.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelectedTile, Selected), UCanBeOwned::StaticClass());
}

EBTNodeResult::Type UBuySelectedTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

void UBuySelectedTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UBuySelectedTile::BuySelected(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UObject* ObjectToBuy)
{
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBuySelectedTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
