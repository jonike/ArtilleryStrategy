// Fill out your copyright notice in the Description page of Project Settings.


#include "HeightFluctuationPass.h"
#include "Structs/WorldParams.h"

void UHeightFluctuationPass::GenerateWorld(FWorldParams& Params)
{
	for (auto Row = 0; Row < Params.HeightMatrix.GetRows(); ++Row)
	{
		for (auto Column = 0; Column < Params.HeightMatrix.GetColumns(); ++Column)
		{
			if (IsFluctuationOccured())
			{
				Params.HeightMatrix.Get(Row, Column) += FluctuationDirection;
			}
		}
	}
}

bool UHeightFluctuationPass::IsFluctuationOccured() const
{
	return FMath::RandRange(0.f, 1.f) < FluctuationChance;
}
