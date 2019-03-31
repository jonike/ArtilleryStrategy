// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResourceWidgetInterface.generated.h"

struct FResource;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResourceWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API IResourceWidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Fill(const FName& Name, const FResource& Resource) = 0;
};
