// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Engine/World.h"
#include "Game/Modes/ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"
#include "Objects/TileMatrix.h"
#include "Components/CapitalPlacementGenerator.h"
#include "Components/ResourceDepositGenerator.h"
#include "Components/TurnProcessorComponent.h"

ADefaultGS::ADefaultGS()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	Matrix = CreateDefaultSubobject<UTileMatrix>(TEXT("Tile matrix"));
	CapitalPlacementGenerator = CreateDefaultSubobject<UCapitalPlacementGenerator>(TEXT("Capital placement"));
	ResourceDepositGenerator = CreateDefaultSubobject<UResourceDepositGenerator>(TEXT("Resource deposits"));
	TurnProcessorComponent = CreateDefaultSubobject<UTurnProcessorComponent>(TEXT("Turn processor component"));
}

UTurnProcessorComponent* ADefaultGS::GetTurnProcessor() const
{
	return TurnProcessorComponent;
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	const auto Generator = GetGridGenerator();
	Generator->OnGridGenerationStart.AddDynamic(this, &ADefaultGS::ReceiveOnGridGenerationStarted);
	Generator->OnTileGenerated.AddDynamic(this, &ADefaultGS::ReceiveOnTileGenerated);
	Generator->OnGridGenerationEnd.AddDynamic(this, &ADefaultGS::ReceiveOnGridGenerationEnd);
}

void ADefaultGS::ReceiveOnGridGenerationStarted(const int Rows, const int Columns)
{
	Matrix->Resize(Rows, Columns);
}

void ADefaultGS::ReceiveOnTileGenerated(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column)
{
	Matrix->Get(Row, Column) = Tile;
}

void ADefaultGS::ReceiveOnGridGenerationEnd(int Rows, int Columns)
{
	OnGridGenerationEnded.Broadcast(Matrix);
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
