// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "ScriptInterface.h"
#include "Structs/ResourcePack.h"
#include "PlayerProperty.generated.h"

class IOwnerController;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerProperty : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Represents anything that can be owned by one player
 */
class ARTILLERYSTRATEGY_API IPlayerProperty
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool HasOwnerController() const = 0;

	virtual TScriptInterface<IOwnerController> GetOwnerController() const = 0;

	virtual void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) = 0;

	/**
	 * \brief Check if this object requires resources to own
	 * \return whether this requires resources to acquire it
	 */
	virtual bool RequiresResourcesToOwn() const = 0;

	virtual const FResourcePack& GetResourcesToOwn() const = 0;
};
