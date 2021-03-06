// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Objects/ResourceStorage.h"
#include "PlayerRepository.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UPlayerRepository : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Class that holds all actives that player has
 */
class ARTILLERYSTRATEGY_API IPlayerRepository
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
		virtual UResourceStorage* GetResourceWallet() const = 0;
};
