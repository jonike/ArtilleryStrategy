// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceWeaponBuilding.h"
#include "Libraries/ASLibrary.h"
#include "Objects/TileMatrix.h"
#include "Interfaces/PlayerProperty.h"
#include "Structs/BuildingData.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/OwnerController.h"

UPlaceWeaponBuilding::UPlaceWeaponBuilding()
{
}

EBTNodeResult::Type UPlaceWeaponBuilding::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO: add check whether owner has enough resources to create building
	// TODO: add check whether the AI controller can buy anything on this turn
	const auto Tile = GetTile(OwnerComp);
	const auto BuildingClass = GetBuildingClass(OwnerComp);
	if (Tile.GetObject() && BuildingClass.Get())
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
	const auto& Params = UASLibrary::GetWorldParams(&OwnerComp);
	const auto Rows = Params.GetRows();
	const auto Columns = Params.GetColumns();
	const auto SelfOwnerController = TScriptInterface<IOwnerController>(OwnerComp.GetAIOwner());
	// If controller can own something
	if (SelfOwnerController)
	{
		// TODO: remove nested for loops
		for (auto Row = 0; Row < Rows; ++Row)
		{
			for (auto Column = 0; Column < Columns; ++Column)
			{
				const auto Tile = Params.GetTileMatrix()->Get(Row, Column);
				const auto TileAsProperty = Cast<IPlayerProperty>(Tile.GetObject());
				// If tile is a property && it doesn't have building && it is owned by our controller
				if (TileAsProperty
					&& !Tile->HasBuilding()
					&& TileAsProperty->GetOwnerController() == SelfOwnerController)
				{
					return Tile;
				}
			}
		}
	}
	return nullptr;
}

TSubclassOf<AActor> UPlaceWeaponBuilding::GetBuildingClass(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Names = WeaponBuildingsTable->GetRowNames();
	if (Names.Num() > 0)
	{
		const auto BuildingInfo = WeaponBuildingsTable->FindRow<FBuildingData>(Names.Top(), TEXT("Get weapon building data for spawning weapons for AI"));
		return BuildingInfo->SpawnClass;
	}
	return nullptr;
}

void UPlaceWeaponBuilding::SpawnBuilding(UBehaviorTreeComponent& OwnerComp, TScriptInterface<IWorldTile> Tile, TSubclassOf<AActor> BuildingClass) const
{
	const auto SpawnedBuilding = Tile->SpawnBuilding(BuildingClass);
	const auto PlayerState = OwnerComp.GetAIOwner()->GetPlayerState<ADefaultPlayerState>();
	check(PlayerState);
	PlayerState->RegisterBuyingBuilding(SpawnedBuilding);
}
