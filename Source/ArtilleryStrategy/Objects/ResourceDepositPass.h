// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "Structs/ResourceHandle.h"
#include "ResourceDepositPass.generated.h"

class IWorldTile;
struct FResource;
class ISpawnStrategy;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceDepositPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	virtual FResourceHandle GetRandomResource() const;
	virtual int32 GetRandomResourceAmount(const FResource& Resource) const;
	virtual TScriptInterface<IWorldTile> GetTileForDeposit(const FWorldParams& Params) const;

private:
	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	int DepositsAmount = 4;

	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	TArray<FResourceHandle> AvailableDeposits;

	void CreateDeposits(const FWorldParams& Params) const;
};
