// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Projectile.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProjectile : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Represents projectiles that are influenced by gravity (bullets, etc)
 */
class ARTILLERYSTRATEGY_API IProjectile
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddImpulse(float Value) = 0;
};
