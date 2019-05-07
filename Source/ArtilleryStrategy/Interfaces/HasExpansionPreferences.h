// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasExpansionPreferences.generated.h"

class UExpansionPreferences;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasExpansionPreferences : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API IHasExpansionPreferences
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UExpansionPreferences* GetExpansionPreferences() = 0;
	virtual const UExpansionPreferences* GetExpansionPreferences() const = 0;
};
