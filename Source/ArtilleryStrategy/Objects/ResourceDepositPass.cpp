// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDepositPass.h"
#include "Structs/Resource.h"
#include "Structs/ResourceDeposit.h"
#include "Interfaces/WorldTile.h"
#include "Structs/WorldParams.h"
#include "TileMatrix.h"

void UResourceDepositPass::GenerateWorld(FWorldParams& Params)
{
	CreateDeposits(Params);
}

FResourceHandle UResourceDepositPass::GetRandomResource() const
{
	const auto Index = FMath::RandRange(0, AvailableDeposits.Num() - 1);
	return AvailableDeposits[Index];
}

int32 UResourceDepositPass::GetRandomResourceAmount(const FResource& Resource) const
{
	return FMath::RandRange(Resource.MinAmountSpawned, Resource.MaxAmountSpawned);
}

void UResourceDepositPass::CreateDeposits(const FWorldParams& Params) const
{
	for (size_t i = 0; i < DepositsAmount; i++)
	{
		FResourceDeposit ResourceDeposit;
		ResourceDeposit.ResourceAmount.ResourceHandle = GetRandomResource();
		ResourceDeposit.ResourceAmount.Amount = GetRandomResourceAmount(ResourceDeposit.ResourceAmount.GetResource(TEXT("Getting resource data for spawning deposits")));
		GetTileForDeposit(Params)->SetResourceDeposits(ResourceDeposit);
	}
}

TScriptInterface<IGridPlatform> UResourceDepositPass::GetTileForDeposit(const FWorldParams& Params) const
{
	const auto Row = FMath::RandRange(0, Params.TileMatrix->GetRows() - 1);
	const auto Column = FMath::RandRange(0, Params.TileMatrix->GetColumns() - 1);
	return Params.TileMatrix->Get(Row, Column);
}
