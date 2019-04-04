// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Engine/World.h"
#include "Game/Modes/ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"
#include "Interfaces/SpawnStrategy.h"

ADefaultGS::ADefaultGS()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	CapitalPlacementGenerator = CreateDefaultSubobject<UCapitalPlacementGenerator>(TEXT("Capital placement generator"));
	Matrix = CreateDefaultSubobject<UTileMatrix>(TEXT("Tile matrix"));
}

TScriptInterface<ISpawnStrategy> ADefaultGS::GetCapitalSpawnStrategy() const
{
	return CapitalSpawnStrategy;
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CapitalSpawnStrategy = NewObject<UObject>(this, CapitalSpawnStrategyClass);
	CapitalSpawnStrategy->SetTileMatrix(Matrix);

	const auto Generator = GetGridGenerator();
	Generator->OnGridGenerationStart.AddDynamic(this, &ADefaultGS::ReceiveOnGridGenerationStarted);
	Generator->OnTileGenerated.AddDynamic(this, &ADefaultGS::ReceiveOnTileGenerated);
	Generator->OnGridGenerationEnd.AddDynamic(GetCapitalPlacementGenerator(), &UCapitalPlacementGenerator::ReceiveOnGridGenerationEnd);
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

void ADefaultGS::AddTile(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column) const
{
	Matrix->Get(Row, Column) = Tile;
}

void ADefaultGS::ResizeTileMatrix(const int Rows, const int Columns) const
{
	Matrix->Resize(Rows, Columns);
}

UCapitalPlacementGenerator* ADefaultGS::GetCapitalPlacementGenerator() const
{
	return CapitalPlacementGenerator;
}
