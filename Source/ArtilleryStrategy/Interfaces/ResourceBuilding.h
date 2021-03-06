// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceBuilding.generated.h"

struct FResource;
struct FResourceDeposit;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResourceBuilding : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Represents resource buildings (buildings that can produce resources)
 */
class ARTILLERYSTRATEGY_API IResourceBuilding
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual TSet<FResourceDeposit>& GetProducingResources() = 0;

	virtual bool IsProducingResource() const = 0;

	virtual void AddResourceDeposit(FResourceDeposit& Deposit) = 0;
};
