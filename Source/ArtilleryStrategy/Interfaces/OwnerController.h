// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Wallet.h"
#include "OwnerController.generated.h"

class UMaterialInterface;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOwnerController : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Controller that can own property
 */
class ARTILLERYSTRATEGY_API IOwnerController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UMaterialInterface* GetOwnerMaterial() const = 0;

	virtual UTexture2D* GetOwnerIcon() const = 0;

	virtual TScriptInterface<IWallet> GetWallet() const = 0;
};
