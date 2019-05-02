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
 * \brief Class that wants to now when turn starts and ends
 */
class ARTILLERYSTRATEGY_API ITurnDependent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	/**
	 * \brief Can be bound to call when new turn started
	 */
	UFUNCTION()
	virtual void ReceiveOnTurnStarted();

	/**
	 * \brief Can be bound to call when the turn ends
	 */
	UFUNCTION()
	virtual void ReceiveOnTurnEnded();

	/**
	 * \brief Get component to which we can bind our methods
	 * \param Context Any object in the current UWorld
	 * \return turn processor
	 */
	virtual UTurnProcessorComponent* GetTurnProcessor(const UObject* Context) const;
};
