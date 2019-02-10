// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtilleryStrategyGMB.h"
#include "GridGenerator.h"

AArtilleryStrategyGMB::AArtilleryStrategyGMB()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
}

void AArtilleryStrategyGMB::BeginPlay()
{
	check(GridGenerator);

	GridGenerator->GenerateGrid();
}
