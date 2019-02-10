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


// Called every frame
void UGridGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridGenerator::GenerateGrid()
{
	if (GEngine)
	{
		UE_LOG(GridGeneration, Log, TEXT("Grid generation started"));
	}
}

