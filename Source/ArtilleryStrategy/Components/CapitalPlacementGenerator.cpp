// Fill out your copyright notice in the Description page of Project Settings.

#include "CapitalPlacementGenerator.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"
#include "Actors/CapitalBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Game/States/DefaultGS.h"
#include "Interfaces/CanBeOwned.h"
#include "GridGenerator.h"

// Sets default values for this component's properties
UCapitalPlacementGenerator::UCapitalPlacementGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCapitalPlacementGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void UCapitalPlacementGenerator::ReceiveOnGridGenerationEnd(int Rows, int Columns)
{
	PlaceCapitalsForAll();
}

void UCapitalPlacementGenerator::PlaceCapital(TScriptInterface<IOwnerController> Controller) const
{
	check(Controller);
	const auto Cell = GetSpawnCell();
	auto Property = Cast<ICanBeOwned>(Cell.GetObject());
	check(Property);
	Property->SetOwnerController(GetWorld()->GetFirstPlayerController());
	const auto Capital = CreateCapitalBuilding(Cell->GetBuildingSpawnLocation());
	SetupCapitalBuilding(Capital, Controller);
}

ACapitalBuilding* UCapitalPlacementGenerator::CreateCapitalBuilding(FVector Location) const
{
	const auto Spawned = GetWorld()->SpawnActor(CapitalActorClass, &Location);
	return Cast<ACapitalBuilding>(Spawned);
}

TScriptInterface<IGridPlatform> UCapitalPlacementGenerator::GetSpawnCell() const
{
	const auto GameState = Cast<ADefaultGS>(GetWorld()->GetGameState());
	check(GameState);
	return GameState->GetTileForCapital();
}

void UCapitalPlacementGenerator::SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const
{
	Capital->SetOwnerController(Controller);
}

// Called every frame
void UCapitalPlacementGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCapitalPlacementGenerator::PlaceCapitalsForAll() const
{
	auto ControllerIterator = GetWorld()->GetControllerIterator();
	while (ControllerIterator)
	{
		PlaceCapital(ControllerIterator->Get());
		++ControllerIterator;
	}
}
