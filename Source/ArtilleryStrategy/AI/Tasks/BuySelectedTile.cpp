// Fill out your copyright notice in the Description page of Project Settings.

#include "BuySelectedTile.h"
#include "Interfaces/WorldTile.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/PlayerProperty.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AI/Controllers/DefaultAIController.h"
#include "Libraries/CoreLibrary.h"

UBuySelectedTile::UBuySelectedTile()
{
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelectedTile, SelectedTile), UPlayerProperty::StaticClass());
	SelectedTile.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBuySelectedTile, SelectedTile), UWorldTile::StaticClass());
}

EBTNodeResult::Type UBuySelectedTile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto AIOwner = OwnerComp.GetAIOwner();
	if (const auto PlayerState = AIOwner->GetPlayerState<ADefaultPlayerState>())
	{
		// There is stored object in the key
		if (const auto StoredObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(SelectedTile.SelectedKeyName))
		{
			// The stored objects has correct type
			if (const auto Tile = Cast<IPlayerProperty>(StoredObject))
			{
				const auto& RequiredResources = Tile->GetResourcesToOwn();
				// Have enough resources
				if (PlayerState->GetResourceWallet()
					->IsEnoughPack(RequiredResources))
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
	// Can buy tiles
	if (const auto Controller = Cast<ICanBuyTiles>(OwnerComp.GetAIOwner()))
	{
		// Object can be bought
		if (Cast<IPlayerProperty>(ObjectToBuy))
		{
			// Can buy tiles on this turn
			if (!UCoreLibrary::GetPlayerTurnLimitsForController(OwnerComp.GetAIOwner())
				.GetTilesLimit()
				.IsLimitReached())
			{
				Controller->BuyTile(ObjectToBuy);
				// Clear keys if necessary
				if (bShouldClearSelectedTile)
				{
					OwnerComp.GetBlackboardComponent()->ClearValue(SelectedTile.SelectedKeyName);
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBuySelectedTile::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}
