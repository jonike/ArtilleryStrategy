// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Interface.h"
#include "WorldGenerationPass.generated.h"

struct FWorldParams;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWorldGenerationPass : public UInterface
{
	GENERATED_BODY()
};

/**
 * \brief Pass for world generation which works with FWorldParams
 */
class ARTILLERYSTRATEGY_API IWorldGenerationPass
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GenerateWorld(FWorldParams& Params) = 0;
};
