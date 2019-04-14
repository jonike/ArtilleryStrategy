// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/ResourceBuilding.h"
#include "Engine/DataTable.h"
#include "Structs/ResourceDeposit.h"
#include "ScriptInterface.h"
#include "BaseResourceBuilding.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseResourceBuilding : public ABaseBuilding, public IResourceBuilding
{
	GENERATED_BODY()

public:
	void ReceiveOnTurnEnded() override;

	// Inherited via IResourceBuilding
	bool IsProducingResource() const override;
	void AddResourceDeposit(FResourceDeposit& Deposit) override;
	TSet<FResourceDeposit>& GetProducingResources() override;

	void PostPlaced(TScriptInterface<IGridPlatform> Tile) override;

private:
	UPROPERTY(Category = "Production", EditDefaultsOnly)
	TSet<FResourceHandle> ResourcesCanProduce;

	UPROPERTY(Category = "Production", VisibleInstanceOnly)
	TSet<FResourceDeposit> ProducedResources;

	void PopulateProducedResourcesContainer(TScriptInterface<IGridPlatform> Tile);
};
