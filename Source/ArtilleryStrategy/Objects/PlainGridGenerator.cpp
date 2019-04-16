// Fill out your copyright notice in the Description page of Project Settings.


#include "PlainGridGenerator.h"
#include "Engine/World.h"

void UPlainGridGenerator::Generate(const FWorldParams& Params)
{
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
			const auto SpawnedTile = SpawnPlatform(Location);
		}
	}
}

AActor* UPlainGridGenerator::SpawnPlatform(const FVector& Location) const
{
	auto Platform = GetWorld()->SpawnActor<AActor>(GridPlatformClass, Location, FRotator::ZeroRotator);
#if WITH_EDITOR
	Platform->SetFolderPath(TEXT("World/Platforms"));
#endif
	return Platform;
}
