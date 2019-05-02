// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/ResourceBuilding.h"
#include "Structs/ResourceDeposit.h"
#include "ScriptInterface.h"
#include "BaseResourceBuilding.generated.h"

/**
 * \brief Base class for buildings that can produce resources
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
	/**
	 * \brief A list of resources the building ***CAN*** produce
	 */
	UPROPERTY(Category = "Production", EditDefaultsOnly)
	TSet<FResourceHandle> ResourcesCanProduce;

	/**
	 * \brief A list of resources the building is producing currently
	 */
	UPROPERTY(Category = "Production", VisibleInstanceOnly)
	TSet<FResourceDeposit> ProducedResources;

	/**
	 * \brief Populate a list of producing resources
	 * \param Tile The tile this building is placed on
	 */
	void PopulateProducedResourcesContainer(TScriptInterface<IGridPlatform> Tile);
};
