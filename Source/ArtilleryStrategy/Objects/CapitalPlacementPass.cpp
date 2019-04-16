// Fill out your copyright notice in the Description page of Project Settings.


#include "CapitalPlacementPass.h"
#include "Structs/WorldParams.h"
#include "Engine/World.h"
#include "Actors/CapitalBuilding.h"
#include "Objects/TileMatrix.h"
#include "Interfaces/GridPlatform.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBeOwned.h"

void UCapitalPlacementPass::GenerateWorld(FWorldParams& Params)
{
	WorldParams = Params;
	const auto World = Params.CurrentWorld;
	check(World);
	auto ControllerIterator = World->GetControllerIterator();
	while (ControllerIterator)
	{
		PlaceCapital(ControllerIterator->Get());
		++ControllerIterator;
	}
}

TScriptInterface<IGridPlatform> UCapitalPlacementPass::GetSpawnCell() const
{
	const auto Matrix = WorldParams.TileMatrix;
	check(Matrix);
	const auto Row = FMath::RandRange(0, Matrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix->GetColumns() - 1);
	return Matrix->Get(Row, Column);
}

void UCapitalPlacementPass::PlaceCapital(TScriptInterface<IOwnerController> Controller) const
{
	check(Controller);
	const auto Cell = GetSpawnCell();
	auto Property = Cast<ICanBeOwned>(Cell.GetObject());
	check(Property);
	Property->SetOwnerController(WorldParams.CurrentWorld->GetFirstPlayerController());
	const auto Capital = CreateCapitalBuilding(Cell->GetBuildingSpawnLocation());
	SetupCapitalBuilding(Capital, Controller);
}

ACapitalBuilding* UCapitalPlacementPass::CreateCapitalBuilding(FVector Location) const
{
	const auto Spawned = WorldParams.CurrentWorld->SpawnActor(CapitalActorClass, &Location);
	return Cast<ACapitalBuilding>(Spawned);
}

void UCapitalPlacementPass::SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const
{
	Capital->SetOwnerController(Controller);
}
