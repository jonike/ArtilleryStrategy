// Fill out your copyright notice in the Description page of Project Settings.

#include "OffsetSmoothingPass.h"
#include "Structs/WorldParams.h"
#include "TileMatrix.h"
#include "GameFramework/Actor.h"

void UDEPRECATED_OffsetSmoothingPass::GenerateWorld(FWorldParams& Params)
{
	const auto* Matrix = Params.TileMatrix;
	for (auto Row = SmoothRadius; Row < Matrix->GetRows() - SmoothRadius; ++Row)
	{
		for (auto Column = SmoothRadius; Column < Matrix->GetColumns() - SmoothRadius; ++Column)
		{
			const auto Deviance = CalculateDevianceLevel(Params, Row, Column);
			if (Deviance < MinDevianceLevel || Deviance > MaxDevianceLevel)
			{
				SmoothTile(Matrix->Get(Row, Column), Deviance);
			}
		}
	}
}

void UDEPRECATED_OffsetSmoothingPass::SmoothTile(const TScriptInterface<IGridPlatform> Tile, const int Deviance)
{
	const auto TileActor = Cast<AActor>(Tile.GetObject());
	check(TileActor);
	const FVector Offset(0, 0, - FMath::Sign(Deviance) * OffsetPerDeviancePoint);
	TileActor->AddActorWorldOffset(Offset, false, nullptr, ETeleportType::TeleportPhysics);
}

int UDEPRECATED_OffsetSmoothingPass::CalculateDevianceLevel(const FWorldParams& Params, const int TileRow, const int TileColumn)
{
	const auto* Matrix = Params.TileMatrix;
	auto Deviance = 0;
	for (auto Row = TileRow - SmoothRadius; Row <= TileRow + SmoothRadius; ++Row)
	{
		for (auto Column = TileColumn - SmoothRadius; Column <= TileColumn + SmoothRadius; ++Column)
		{
			if (Row == TileRow && Column == TileColumn)
			{
				continue;
			}

			if (Matrix->IsValidIndex(Row, Column))
			{
				Deviance += CalculateDevianceForPair(Matrix->Get(TileRow, TileColumn), Matrix->Get(Row, Column));
			}
		}
	}
	return Deviance;
}

int UDEPRECATED_OffsetSmoothingPass::CalculateDevianceForPair(const TScriptInterface<IGridPlatform> AnalyzedTile, const TScriptInterface<IGridPlatform> NeighborTile) const
{
	const auto AnalyzedActor = Cast<AActor>(AnalyzedTile.GetObject());
	check(AnalyzedActor);
	const auto NeighborActor = Cast<AActor>(NeighborTile.GetObject());
	check(NeighborActor);
	const auto AnalyzedLocation = AnalyzedActor->GetActorLocation();
	const auto NeighborLocation = NeighborActor->GetActorLocation();
	if (AnalyzedLocation.Z > NeighborLocation.Z)
	{
		return +1;
	}
	if (AnalyzedLocation.Z < NeighborLocation.Z)
	{
		return -1;
	}
	return 0;
}
