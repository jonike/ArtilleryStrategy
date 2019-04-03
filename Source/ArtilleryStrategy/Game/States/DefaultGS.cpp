// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Engine/World.h"
#include "Game/Modes/ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"

ADefaultGS::ADefaultGS()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	CapitalPlacementGenerator = CreateDefaultSubobject<UCapitalPlacementGenerator>(TEXT("Capital placement generator"));
	Matrix = CreateDefaultSubobject<UTileMatrix>(TEXT("Tile matrix"));
}

TScriptInterface<IGridPlatform> ADefaultGS::GetTileForCapital() const
{
	const auto Row = FMath::RandRange(0, Matrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix->GetColumns() - 1);
	return Matrix->Get(Row, Column);
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//Matrix = NewObject<UTileMatrix>();
	const auto Generator = GetGridGenerator();
	Generator->OnGridGenerationStart.AddDynamic(this, &ADefaultGS::ReceiveOnGridGenerationStarted);
	Generator->OnTileGenerated.AddDynamic(this, &ADefaultGS::ReceiveOnTileGenerated);
}

void ADefaultGS::BeginPlay()
{
	GetGridGenerator()->GenerateGrid();
	GetCapitalPlacementGenerator()->PlaceCapitalsForAll();
}


void ADefaultGS::ReceiveOnGridGenerationStarted(const int Rows, const int Columns)
{
	Matrix->Resize(Rows, Columns);
}

void ADefaultGS::ReceiveOnTileGenerated(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column)
{
	Matrix->Get(Row, Column) = Tile;
}

UGridGenerator* ADefaultGS::GetGridGenerator() const
{
	return GridGenerator;
}

UCapitalPlacementGenerator* ADefaultGS::GetCapitalPlacementGenerator() const
{
	return CapitalPlacementGenerator;
}
