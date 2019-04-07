// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurnDependent.generated.h"

class UTurnProcessorComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTurnDependent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARTILLERYSTRATEGY_API ITurnDependent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
	virtual void ReceiveOnTurnStarted();

	UFUNCTION()
	virtual void ReceiveOnTurnEnded();

	virtual UTurnProcessorComponent* GetTurnProcessor(UObject* Context) const;
};
