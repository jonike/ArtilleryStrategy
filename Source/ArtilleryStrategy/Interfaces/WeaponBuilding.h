// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WeaponBuilding.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWeaponBuilding : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Building that can fire during turn
 */
class ARTILLERYSTRATEGY_API IWeaponBuilding
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Fire() = 0;

	virtual void SetPlaneAngle(float Angle) = 0;

	virtual void SetHorizonAngle(float Angle) = 0;

	virtual bool IsReadyForFire() const = 0;
};
