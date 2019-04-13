// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScriptInterface.h"
#include "Structs/ResourcePack.h"
#include "CanBeOwned.generated.h"

class IOwnerController;

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
	virtual TScriptInterface<IOwnerController> GetOwnerController() const = 0;
	virtual void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) = 0;

	virtual bool RequiresResourcesToOwn() const = 0;
	virtual FResourcePack GetResourcesToOwn() const = 0;
};
