// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/ResourceBuilding.h"
#include "Engine/DataTable.h"
#include "Structs/ResourceDeposit.h"
#include "BaseResourceBuilding.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseResourceBuilding : public ABaseBuilding, public IResourceBuilding
{
	GENERATED_BODY()

public:
	// Inherited via IResourceBuilding
	bool IsProducingResource() const override;
	void AddResourceDeposit(FResourceDeposit& Deposit) override;
	TArray<FResourceDeposit>& GetProducingResource() override;

	void PostPlaced(TScriptInterface<IGridPlatform> Tile) override;

	void ReceiveOnTurnEnded() override;

private:
	UPROPERTY(Category = "Production|Resources", EditAnywhere)
	TArray<FResourceDeposit> ProducedResources;
};
