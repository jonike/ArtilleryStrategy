// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Controllers/DefaultAIController.h"
#include "AdvancedAIController.generated.h"

class UExpansionPreferences;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API AAdvancedAIController : public ADefaultAIController
{
	GENERATED_BODY()

public:
	AAdvancedAIController();

	UExpansionPreferences* GetExpansionPreferences() const;

private:
	UPROPERTY(EditAnywhere)
	UExpansionPreferences* Preferences;
};
