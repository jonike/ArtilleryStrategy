// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/ResourceBuilding.h"
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
	void AddResourceDeposit(UResourceDeposit* Deposit) override;
	UResourceDeposit* GetProducingResource() const override;

private:
	UPROPERTY(Category = "Production|Resources", EditAnywhere)
	UResourceDeposit* ProducedResource;
};
