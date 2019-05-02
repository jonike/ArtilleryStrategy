// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "FireManager.generated.h"

class IWeaponBuilding;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFireManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief An object that decides when to fire owned weapon
 */
class ARTILLERYSTRATEGY_API IFireManager
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * \brief Binds weapon to the manager so it can fire when needed
	 * \param Weapon weapon to add to the list
	 */
	virtual void AddToFireList(TScriptInterface<IWeaponBuilding> Weapon) = 0;
};
