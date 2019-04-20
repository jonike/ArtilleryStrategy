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
	const auto World = Params.CurrentWorld;
	check(World);
	auto ControllerIterator = World->GetControllerIterator();
	while (ControllerIterator)
	{
		PlaceCapital(ControllerIterator->Get(), Params);
		++ControllerIterator;
	}
}

TScriptInterface<IGridPlatform> UCapitalPlacementPass::GetSpawnCell(const FWorldParams& Params) const
{
	const auto Matrix = Params.TileMatrix;
	check(Matrix);
	const auto Row = FMath::RandRange(0, Matrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix->GetColumns() - 1);
	return Matrix->Get(Row, Column);
}

void UCapitalPlacementPass::PlaceCapital(const TScriptInterface<IOwnerController> Controller, const FWorldParams& Params) const
{
	check(Controller);
	const auto Cell = GetSpawnCell(Params);
	auto Property = Cast<ICanBeOwned>(Cell.GetObject());
	check(Property);
	Property->SetOwnerController(Params.CurrentWorld->GetFirstPlayerController());
	const auto Capital = CreateCapitalBuilding(Cell->GetBuildingSpawnLocation(), Params);
	SetupCapitalBuilding(Capital, Controller);
}

ACapitalBuilding* UCapitalPlacementPass::CreateCapitalBuilding(FVector Location, const FWorldParams& Params) const
{
	const auto Spawned = Params.CurrentWorld->SpawnActor(CapitalActorClass, &Location);
	return Cast<ACapitalBuilding>(Spawned);
}

void UCapitalPlacementPass::SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const
{
	Capital->SetOwnerController(Controller);
}
