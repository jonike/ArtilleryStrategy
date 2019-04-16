// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldGenerator.h"
#include "Engine/World.h"
#include "Objects/TileMatrix.h"

// Sets default values for this component's properties
UGridGenerator::UGridGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateWorld();
}

// Called every frame
void UGridGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridGenerator::GenerateWorld()
{
	OnWorldGenerationStart.Broadcast();
	// TODO: having to explicitly call initialize method
	WorldParams.Initialize(this);
	for (const auto& Pass : WorldGenerationPasses)
	{
		Pass->GenerateWorld(WorldParams);
	}
	OnWorldGenerationEnd.Broadcast();
}
