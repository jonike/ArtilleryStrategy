// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "HasSpringArm.generated.h"

class USpringArmComponent;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasSpringArm : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Class that has SpringArm component on it
 */
class ARTILLERYSTRATEGY_API IHasSpringArm
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual USpringArmComponent* GetSpringArmComponent() const = 0;
};
