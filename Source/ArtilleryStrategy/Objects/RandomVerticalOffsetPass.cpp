// Fill out your copyright notice in the Description page of Project Settings.

#include "RandomVerticalOffsetPass.h"
#include "Structs/WorldParams.h"
#include "TileMatrix.h"
#include "GameFramework/Actor.h"

void URandomVerticalOffsetPass::GenerateWorld(FWorldParams& Params)
{
	OffsetAllTiles(Params);
}

void URandomVerticalOffsetPass::OffsetTile(const TScriptInterface<IGridPlatform> Tile)
{
	check(Tile);
	const auto RandomOffset = GetRandomOffset(MinVerticalOffset, MaxVerticalOffset, OffsetStep);
	const FVector Offset(0, 0, RandomOffset);
	const auto TileActor = Cast<AActor>(Tile.GetObject());
	check(TileActor);
	TileActor->AddActorWorldOffset(Offset, false, nullptr, ETeleportType::TeleportPhysics);
}

float URandomVerticalOffsetPass::GetRandomOffset(const float Min, const float Max, const float Step)
{
	const auto Steps = static_cast<int>((Max - Min) / Step);
	const auto RandomStep = FMath::RandRange(0, Steps);
	return Min + Step * RandomStep;
}

void URandomVerticalOffsetPass::OffsetAllTiles(const FWorldParams& Params)
{
	const auto* TileMatrix = Params.TileMatrix;
	for (auto Row = 0; Row < TileMatrix->GetRows(); ++Row)
	{
		for (auto Column = 0; Column < TileMatrix->GetColumns(); ++Column)
		{
			OffsetTile(TileMatrix->Get(Row, Column));
		}
	}
}
