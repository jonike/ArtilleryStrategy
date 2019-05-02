// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "Structs/ResourceHandle.h"
#include "ResourceWidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResourceWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Widget that shows info about one given resource
 */
class ARTILLERYSTRATEGY_API IResourceWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * \brief Shows info about giver resource
	 * \param Resource resource to show info about
	 */
	virtual void SetupResourceWidget(FResourceHandle Resource) = 0;
};
