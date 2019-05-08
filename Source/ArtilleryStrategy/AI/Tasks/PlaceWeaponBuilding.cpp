// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceWeaponBuilding.h"
#include "Libraries/ASLibrary.h"
#include "Objects/TileMatrix.h"
#include "Structs/BuildingData.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyBuildings.h"
#include "Libraries/Tiles.h"

UPlaceWeaponBuilding::UPlaceWeaponBuilding()
{
}

EBTNodeResult::Type UPlaceWeaponBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Tile = GetTile(OwnerComp);
	const auto BuildingClass = GetBuildingClass(OwnerComp);
	if (Tile.GetObject()
		&& BuildingClass.Get()
		&& CanSpawnBuilding(OwnerComp, BuildingClass))
	{
		SpawnBuilding(OwnerComp, Tile, BuildingClass);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UPlaceWeaponBuilding::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UPlaceWeaponBuilding::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

TScriptInterface<IWorldTile> UPlaceWeaponBuilding::GetTile(UBehaviorTreeComponent& OwnerComp) const
{
	const auto SelfOwnerController = TScriptInterface<IOwnerController>(OwnerComp.GetAIOwner());
	// If controller can own something
	if (SelfOwnerController)
	{
		const auto SelfOwner = OwnerComp.GetAIOwner();
		if (const auto OwnerState = SelfOwner->GetPlayerState<IOwnerState>())
		{
			const auto TilesForBuilding = OwnerState->GetOwnedTiles();
			const auto TilesWithoutBuildings = UTiles::FilterOnlyTilesWithoutBuildings(TilesForBuilding);
			if (TilesWithoutBuildings.Num() > 0)
			{
				const auto TileObject = TilesWithoutBuildings.CreateConstIterator();
				return *TileObject;
			}
		}
	}
	return nullptr;
}

TSubclassOf<AActor> UPlaceWeaponBuilding::GetBuildingClass(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Names = WeaponBuildingsTable->GetRowNames();
	for (const auto& Name : Names)
	{
		const auto Building = WeaponBuildingsTable->FindRow<FBuildingData>(Name, TEXT("Finding weapon building for spawning in AI task"));
		if (Building->Type == EBuildingType::Weapon)
		{
			return Building->SpawnClass;
		}
	}
	return nullptr;
}

auto UPlaceWeaponBuilding::SpawnBuilding(UBehaviorTreeComponent& OwnerComp, const TScriptInterface<IWorldTile> Tile, TSubclassOf<AActor> BuildingClass) const -> void
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (const auto ControllerCanBuyBuildings = Cast<ICanBuyBuildings>(Controller))
	{
		ControllerCanBuyBuildings->CreateSelectedBuilding(Tile, BuildingClass);
	}
}

bool UPlaceWeaponBuilding::CanSpawnBuilding(UBehaviorTreeComponent& OwnerComp, TSubclassOf<AActor> BuildingClass) const
{
	const auto OwnerState = OwnerComp.GetAIOwner()->GetPlayerState<IOwnerState>();
	return OwnerState
		&& OwnerState->CanBuyBuilding(BuildingClass->GetDefaultObject());
}
