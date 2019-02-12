// Fill out your copyright notice in the Description page of Project Settings.

#include "GridGenerator.h"
#include "Engine/Engine.h"
#include "ArtilleryStrategy.h"

// Sets default values for this component's properties
UGridGenerator::UGridGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGridGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UGridGenerator::SpawnPlatform(const FVector& Location) const
{
	auto SpawnedPlatform = GetWorld()->SpawnActor<AActor>(GridPlatformClass, Location, FRotator::ZeroRotator);
}

// Called every frame
void UGridGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridGenerator::GenerateGrid() const
{
	check(GridPlatformClass);
	if (GEngine)
	{
		UE_LOG(GridGeneration, Log, TEXT("Grid generation started"));
	}

	FVector Location;
	Location.Z = DefaultZ;
	for (int i = 0; i < Rows; ++i)
	{
		Location.X = i * Distance;
		for (int j = 0; j < Columns; ++j)
		{
			Location.Y = j * Distance;
			SpawnPlatform(Location);
		}
	}
}
