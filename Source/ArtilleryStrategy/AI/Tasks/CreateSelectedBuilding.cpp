// Fill out your copyright notice in the Description page of Project Settings.


#include "CreateSelectedBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Interfaces/PlayerProperty.h"
#include "Interfaces/Building.h"
#include "Interfaces/CanBuyBuildings.h"
#include "AIController.h"
#include "Libraries/ASLibrary.h"
#include "Interfaces/PlayerRepository.h"
#include "BehaviorTree/BlackboardComponent.h"

UCreateSelectedBuilding::UCreateSelectedBuilding()
{
	TileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCreateSelectedBuilding, TileKey), UWorldTile::StaticClass());
	TileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UCreateSelectedBuilding, TileKey), UPlayerProperty::StaticClass());
	TileKey.AllowNoneAsValue(false);

	BuildingClassKey.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UCreateSelectedBuilding, BuildingClassKey), UBuilding::StaticClass());
	BuildingClassKey.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UCreateSelectedBuilding, BuildingClassKey), UPlayerProperty::StaticClass());
	BuildingClassKey.AllowNoneAsValue(false);
}

EBTNodeResult::Type UCreateSelectedBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = Cast<ICanBuyBuildings>(OwnerComp.GetAIOwner());
	const auto Repository = UASLibrary::GetPlayerRepositoryForActor(OwnerComp.GetAIOwner());
	const auto& Limits = UASLibrary::GetPlayerTurnLimitsForController(OwnerComp.GetAIOwner());
	const auto TileObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TileKey.SelectedKeyName);
	auto BuildingClass = OwnerComp.GetBlackboardComponent()->GetValueAsClass(BuildingClassKey.SelectedKeyName);
	if (Controller && Repository && TileObject && BuildingClass)
	{
		const auto DefaultObject = BuildingClass->GetDefaultObject();
		if (const auto Building = Cast<IPlayerProperty>(DefaultObject))
		{
			const auto& RequiredResources = Building->GetResourcesToOwn();
			if (Repository->GetResourceWallet()->IsEnoughPack(RequiredResources)
				&& !Limits.GetBuildingsLimit().IsLimitReached())
			{
				if (auto Tile = Cast<IWorldTile>(TileObject))
				{
					Controller->CreateSelectedBuilding(TileObject, BuildingClass);
					if (bShouldClearTileKey)
					{
						OwnerComp.GetBlackboardComponent()->ClearValue(TileKey.SelectedKeyName);
					}
					if (bShouldClearBuildingClassKey)
					{
						OwnerComp.GetBlackboardComponent()->ClearValue(BuildingClassKey.SelectedKeyName);
					}
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UCreateSelectedBuilding::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UCreateSelectedBuilding::OnGameplayTaskActivated(UGameplayTask& Task)
{
}
