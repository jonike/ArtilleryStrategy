// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "MapGenerator.generated.h"

class UTileMatrix;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDEPRECATED_MapGenerator : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Class that participates in world generation
 */
class ARTILLERYSTRATEGY_API IDEPRECATED_MapGenerator
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION()
	virtual void ReceiveOnGridGenerationEnded(UTileMatrix* Tiles) = 0;
};
