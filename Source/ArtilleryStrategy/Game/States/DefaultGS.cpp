// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Engine/World.h"
#include "Game/Modes/ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"

ADefaultGS::ADefaultGS()
{
	// Why this doesn't work?
	Matrix = CreateDefaultSubobject<UTileMatrix>(TEXT("Tile Matrix"));
}

TScriptInterface<IGridPlatform> ADefaultGS::GetTileForCapital() const
{
	const auto Row = FMath::RandRange(0, Matrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix->GetColumns() - 1);
	return (*Matrix)(Row, Column);
}

void ADefaultGS::BeginPlay()
{
	const auto GridGenerator = GetGridGenerator();
	GridGenerator->OnGridGenerationStart.AddDynamic(this, &ADefaultGS::WhenGridGenerationStarted);
	GridGenerator->OnTileGenerated.AddDynamic(this, &ADefaultGS::WhenTileGenerated);
}


void ADefaultGS::WhenGridGenerationStarted(const int Rows, const int Columns)
{
	Matrix->Reserve(Rows, Columns);
}

void ADefaultGS::WhenTileGenerated(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column)
{
	(*Matrix)(Row, Column) = Tile;
}

UGridGenerator* ADefaultGS::GetGridGenerator() const
{
	// TODO: rewrite code so it will correctly work both on server and clients
	const auto Mode = Cast<AArtilleryStrategyGMB>(GetWorld()->GetAuthGameMode());
	check(Mode);
	return Mode->GetGridGenerator();
}
