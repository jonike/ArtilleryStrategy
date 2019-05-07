// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Controllers/DefaultAIController.h"
#include "Interfaces/HasExpansionPreferences.h"
#include "AdvancedAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API AAdvancedAIController : public ADefaultAIController, public IHasExpansionPreferences
{
	GENERATED_BODY()

public:
	AAdvancedAIController();

	UExpansionPreferences* GetExpansionPreferences() override;
	const UExpansionPreferences* GetExpansionPreferences() const override;

private:
	UExpansionPreferences* Preferences;
};
