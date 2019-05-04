// Fill out your copyright notice in the Description page of Project Settings.

#include "TileSpawnPass.h"
#include "Engine/World.h"
#include "Structs/WorldParams.h"
#include "Objects/TileMatrix.h"
#include "Structs/TileData.h"

FVector UPlainGridPass::CalculateStartLocation(const int Rows, const int Columns) const
{
	const auto OffsetX = -(Rows + 1) * RowSpacing / 2;
	const auto OffsetY = -(Columns + 1) * ColumnSpacing / 2;
	auto Location = FVector(OffsetX, OffsetY, 0);
	Location += OriginOffset;
	return Location;
}

void UPlainGridPass::GenerateGrid(FWorldParams& Params, const int Rows, const int Columns) const
{
	auto Location = CalculateStartLocation(Rows, Columns);
	const auto OffsetY = Location.Y;
	for (auto Row = 0; Row < Rows; ++Row)
	{
		Location.X += RowSpacing;
		Location.Y = OffsetY;
		for (auto Column = 0; Column < Columns; ++Column)
		{
			Location.Y += ColumnSpacing;
			Location.Z = OriginOffset.Z + Params.HeightMatrix.Get(Row, Column) * HeightSpacing;
			const auto TileActor = SpawnPlatform(Params, Location);
			Params.TileMatrix->Get(Row, Column) = TileActor;
			if (const auto Tile = Cast<IWorldTile>(TileActor))
			{
				const FTileData Data({Row, Column});
				Tile->SetTileData(Data);
			}
		}
	}
}

void UPlainGridPass::ResizeTilesMatrix(FWorldParams& Params, int& Rows, int& Columns)
{
	check(!Params.HeightMatrix.Empty());
	Rows = Params.HeightMatrix.GetRows();
	Columns = Params.HeightMatrix.GetColumns();
	Params.TileMatrix->Resize(Rows, Columns);
}

void UPlainGridPass::GenerateWorld(FWorldParams& Params)
{
	check(GridPlatformClass);
	int Rows;
	int Columns;
	ResizeTilesMatrix(Params, Rows, Columns);
	GenerateGrid(Params, Rows, Columns);
}

AActor* UPlainGridPass::SpawnPlatform(const FWorldParams& Params, const FVector& Location) const
{
	const auto CurrentWorld = Params.CurrentWorld;
	check(CurrentWorld);
	auto Platform = CurrentWorld->SpawnActor<AActor>(GridPlatformClass, Location, FRotator::ZeroRotator);
#if WITH_EDITOR
	Platform->SetFolderPath(TEXT("World/Platforms"));
#endif
	return Platform;
}
