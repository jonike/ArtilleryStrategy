// Fill out your copyright notice in the Description page of Project Settings.

#include "CapitalPlacementGenerator.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"
#include "Actors/CapitalBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Game/States/DefaultGS.h"
#include "Interfaces/PlayerProperty.h"
#include "WorldGenerator.h"
#include "Interfaces/SpawnStrategy.h"

// Sets default values for this component's properties
UDEPRECATED_CapitalPlacementGenerator::UDEPRECATED_CapitalPlacementGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UDEPRECATED_CapitalPlacementGenerator::ReceiveOnGridGenerationEnded(UTileMatrix* Tiles)
{
	SpawnStrategy->SetTileMatrix(Tiles);
	PlaceCapitalsForAll();
}

// Called when the game starts
void UDEPRECATED_CapitalPlacementGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void UDEPRECATED_CapitalPlacementGenerator::PlaceCapital(TScriptInterface<IOwnerController> Controller) const
{
	check(Controller);
	const auto Cell = GetSpawnCell();
	auto Property = Cast<IPlayerProperty>(Cell.GetObject());
	check(Property);
	Property->SetOwnerController(GetWorld()->GetFirstPlayerController());
	const auto Capital = CreateCapitalBuilding(Cell->GetBuildingSpawnLocation());
	SetupCapitalBuilding(Capital, Controller);
}

ACapitalBuilding* UDEPRECATED_CapitalPlacementGenerator::CreateCapitalBuilding(FVector Location) const
{
	const auto Spawned = GetWorld()->SpawnActor(CapitalActorClass, &Location);
	return Cast<ACapitalBuilding>(Spawned);
}

TScriptInterface<IGridPlatform> UDEPRECATED_CapitalPlacementGenerator::GetSpawnCell() const
{
	return SpawnStrategy->GetNextSpawnPoint();
}

void UDEPRECATED_CapitalPlacementGenerator::SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const
{
	Capital->SetOwnerController(Controller);
}

// Called every frame
void UDEPRECATED_CapitalPlacementGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDEPRECATED_CapitalPlacementGenerator::InitializeComponent()
{
	Super::InitializeComponent();
	if (SpawnStrategyClass)
	{
		SpawnStrategy = NewObject<UObject>(this, SpawnStrategyClass);
	}
	if (const auto DefaultGS = Cast<ADefaultGS>(GetOwner()))
	{
		// DefaultGS->OnGridGenerationEnded.AddDynamic(this, &UCapitalPlacementGenerator::ReceiveOnGridGenerationEnded);
	}
}

void UDEPRECATED_CapitalPlacementGenerator::PlaceCapitalsForAll() const
{
	auto ControllerIterator = GetWorld()->GetControllerIterator();
	while (ControllerIterator)
	{
		PlaceCapital(ControllerIterator->Get());
		++ControllerIterator;
	}
}
