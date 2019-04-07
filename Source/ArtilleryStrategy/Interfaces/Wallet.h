// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Objects/ResourceStorage.h"
#include "Wallet.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UWallet : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ARTILLERYSTRATEGY_API IWallet
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
	virtual UResourceStorage* GetResourceWallet() const = 0;
};
