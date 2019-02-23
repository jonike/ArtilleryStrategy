// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CanBeOwned.generated.h"

class AController;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCanBeOwned : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ARTILLERYSTRATEGY_API ICanBeOwned
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool HasOwnerController() const = 0;
	virtual AController* GetOwnerController() const = 0;
	virtual void SetOwnerController(AController& NewOwner) = 0;
};
