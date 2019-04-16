// Fill out your copyright notice in the Description page of Project Settings.


#include "PlainGridPass.h"
#include "Engine/World.h"
#include "Structs/WorldParams.h"
#include "Objects/TileMatrix.h"
#include "Interfaces/GridPlatform.h"

void UPlainGridPass::GenerateWorld(FWorldParams& Params)
{
	Params.TileMatrix->Resize(Rows, Columns);
	check(GridPlatformClass);
	const auto OffsetX = -(Rows + 1) * RowSpacing / 2;
	const auto OffsetY = -(Columns + 1) * ColumnSpacing / 2;
	FVector Location(OffsetX, OffsetY, 0);
	Location += OriginOffset;
	for (auto i = 0; i < Rows; ++i)
	{
		Location.X += RowSpacing;
		Location.Y = OffsetY;
		for (auto j = 0; j < Columns; ++j)
		{
			Location.Y += ColumnSpacing;
			const auto SpawnedTile = SpawnPlatform(Params, Location);
			check(SpawnedTile);
			Params.TileMatrix->Get(i, j) = SpawnedTile;
		}
	}
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