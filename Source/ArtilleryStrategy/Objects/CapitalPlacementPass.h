// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/WorldGenerationPass.h"
#include "CapitalPlacementPass.generated.h"

class IWorldTile;
class ACapitalBuilding;
class IOwnerController;
/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UCapitalPlacementPass : public UDataAsset, public IWorldGenerationPass
{
	GENERATED_BODY()

public:
	void GenerateWorld(FWorldParams& Params) override;

protected:
	TScriptInterface<IWorldTile> GetSpawnCell(const FWorldParams& Params) const;

private:
	UPROPERTY(EditAnywhere, Category = Capitals, meta = (MustImplement = "IBuilding"))
	TSubclassOf<ACapitalBuilding> CapitalActorClass;

	void PlaceCapital(TScriptInterface<IOwnerController> Controller, const FWorldParams& Params) const;
	ACapitalBuilding* CreateCapitalBuilding(FVector Location, const FWorldParams& Params) const;
	void SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const;
};
