// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/SpawnStrategy.h"
#include "RandomSpawnStrategy.generated.h"

class UTileMatrix;
/**
 * 
 */
UCLASS(Deprecated)
class ARTILLERYSTRATEGY_API UDEPRECATED_RandomSpawnStrategy : public UObject, public IDEPRECATED_SpawnStrategy
{
	GENERATED_BODY()

public:
	void SetTileMatrix(UTileMatrix* Matrix) override;

	TScriptInterface<IWorldTile> GetNextSpawnPoint() const override;

private:
	UPROPERTY()
	UTileMatrix* TileMatrix;

	UPROPERTY(Category = "Spawn", EditDefaultsOnly)
	int SpawnPoints = 4;

	UPROPERTY(Category = "Spawn", VisibleInstanceOnly)
	int SpawnPointsCreated = 0;
};
