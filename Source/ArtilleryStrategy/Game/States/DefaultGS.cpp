// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Engine/World.h"
#include "Game/Modes/ArtilleryStrategyGMB.h"
#include "Components/GridGenerator.h"

TScriptInterface<IGridPlatform> ADefaultGS::GetTileForCapital() const
{
	const auto Row = FMath::RandRange(0, Matrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Matrix->GetColumns() - 1);
	return (*Matrix)(Row, Column);
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Matrix = NewObject<UTileMatrix>();
	const auto GridGenerator = GetGridGenerator();
	GridGenerator->OnGridGenerationStart.AddDynamic(this, &ADefaultGS::ReceiveOnGridGenerationStarted);
	GridGenerator->OnTileGenerated.AddDynamic(this, &ADefaultGS::ReceiveOnTileGenerated);
}


void ADefaultGS::ReceiveOnGridGenerationStarted(const int Rows, const int Columns)
{
	Matrix->Resize(Rows, Columns);
}

void ADefaultGS::ReceiveOnTileGenerated(const TScriptInterface<IGridPlatform> Tile, const int Row, const int Column)
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
