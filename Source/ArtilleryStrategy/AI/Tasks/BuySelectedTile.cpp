// Fill out your copyright notice in the Description page of Project Settings.

#include "BuySelectedTile.h"
#include "Interfaces/GridPlatform.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/CanBeOwned.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/Controllers/DefaultAIController.h"

UBuySelectedTile::UBuySelectedTile()
{
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelectedTile, SelectedTile), UCanBeOwned::StaticClass());
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelectedTile, SelectedTile), UGridPlatform::StaticClass());
}

EBTNodeResult::Type UBuySelectedTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto PlayerState = Controller->GetPlayerState<ADefaultPlayerState>();
	if (PlayerState)
	{
		if (const auto StoredObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelectedTile.SelectedKeyName))
		{
			if (const auto Tile = Cast<ICanBeOwned>(StoredObject))
			{
				if (PlayerState->GetResourceWallet()->IsEnoughPack(Tile->GetResourcesToOwn()))
				{
					const auto BuyResult = BuySelected(OwnerComp, NodeMemory, StoredObject);;
					return BuyResult;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}

void UBuySelectedTile::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

EBTNodeResult::Type UBuySelectedTile::BuySelected(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, UObject* ObjectToBuy) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto DefaultController = Cast<ADefaultAIController>(Controller);
	if (DefaultController)
	{
		if (const auto Cell = Cast<ICanBeOwned>(ObjectToBuy))
		{
			DefaultController->BuyCell(ObjectToBuy);
			if (bShouldClearSelectedTile)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(SelectedTile.SelectedKeyName, nullptr);
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBuySelectedTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
