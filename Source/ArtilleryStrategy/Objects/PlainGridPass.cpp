// Fill out your copyright notice in the Description page of Project Settings.


#include "PlainGridPass.h"
#include "Engine/World.h"
#include "Structs/WorldParams.h"
#include "Objects/TileMatrix.h"

void UPlainGridPass::GenerateWorld(FWorldParams& Params)
{
	// TODO: refactor code
	check(!Params.HeightMatrix.Empty());
	const auto Rows = Params.HeightMatrix.GetRows();
	const auto Columns = Params.HeightMatrix.GetColumns();
	Params.TileMatrix->Resize(Rows, Columns);
	check(GridPlatformClass);
	const auto OffsetX = -(Rows + 1) * RowSpacing / 2;
	const auto OffsetY = -(Columns + 1) * ColumnSpacing / 2;
	FVector Location(OffsetX, OffsetY, 0);
	Location += OriginOffset;
	for (auto Row = 0; Row < Rows; ++Row)
	{
		Location.X += RowSpacing;
		Location.Y = OffsetY;
		for (auto Column = 0; Column < Columns; ++Column)
		{
			check(Params.HeightMatrix.IsValidIndex(Row, Column));
			Location.Y += ColumnSpacing;
			Location.Z = OriginOffset.Z + Params.HeightMatrix.Get(Row, Column);
			const auto SpawnedTile = SpawnPlatform(Params, Location);
			check(SpawnedTile);
			Params.TileMatrix->Get(Row, Column) = SpawnedTile;
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
