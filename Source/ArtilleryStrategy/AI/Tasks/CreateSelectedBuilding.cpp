// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateSelectedBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Interfaces/PlayerProperty.h"
#include "Interfaces/Building.h"
#include "Interfaces/CanBuyBuildings.h"
#include "AIController.h"
#include "Libraries/CoreLibrary.h"
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

void UCreateSelectedBuilding::ClearKeys(UBehaviorTreeComponent& OwnerComp)
{
	// Clear keys if needed
	if (bShouldClearTileKey)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(TileKey.SelectedKeyName);
	}
	if (bShouldClearBuildingClassKey)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(BuildingClassKey.SelectedKeyName);
	}
}

bool UCreateSelectedBuilding::IsEnoughResources(const TScriptInterface<IPlayerRepository> Repository, const FResourcePack& RequiredResources)
{
	return Repository->GetResourceWallet()->IsEnoughPack(RequiredResources);
}

bool UCreateSelectedBuilding::IsLimitNotReached(const FPlayerTurnLimits& Limits)
{
	return !Limits.GetBuildingsLimit().IsLimitReached();
}

UBlackboardComponent::Super::Super* UCreateSelectedBuilding::UnpackTileObject(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsObject(TileKey.SelectedKeyName);
}

UClass* UCreateSelectedBuilding::UnpackBuildingClass(UBehaviorTreeComponent& OwnerComp)
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsClass(BuildingClassKey.SelectedKeyName);
}

EBTNodeResult::Type UCreateSelectedBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Controller can buy buildings
	if (const auto Controller = Cast<ICanBuyBuildings>(OwnerComp.GetAIOwner()))
	{
		// Has repository with resources
		if (const auto Repository = UCoreLibrary::GetPlayerRepositoryForActor(OwnerComp.GetAIOwner()))
		{
			// Unpack tile object
			if (const auto TileObject = UnpackTileObject(OwnerComp))
			{
				// Unpack building class
				if (auto BuildingClass = UnpackBuildingClass(OwnerComp))
				{
					const auto DefaultObject = BuildingClass->GetDefaultObject();
					// Object of stored class can be bought
					if (const auto Building = Cast<IPlayerProperty>(DefaultObject))
					{
						const auto& Limits = UCoreLibrary::GetPlayerTurnLimitsForController(OwnerComp.GetAIOwner());
						const auto& RequiredResources = Building->GetResourcesToOwn();
						if (IsEnoughResources(Repository, RequiredResources)
							&& IsLimitNotReached(Limits))
						{
							Controller->CreateSelectedBuilding(TileObject, BuildingClass);
							ClearKeys(OwnerComp);
							return EBTNodeResult::Succeeded;
						}
					}
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
