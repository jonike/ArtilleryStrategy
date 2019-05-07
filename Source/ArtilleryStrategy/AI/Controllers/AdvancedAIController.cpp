// Fill out your copyright notice in the Description page of Project Settings.


#include "AdvancedAIController.h"
#include "Objects/ExpansionPreferences.h"

AAdvancedAIController::AAdvancedAIController()
{
	Preferences = CreateDefaultSubobject<UExpansionPreferences>(TEXT("Preferences"));
}

UExpansionPreferences* AAdvancedAIController::GetExpansionPreferences()
{
	return Preferences;
}

const UExpansionPreferences* AAdvancedAIController::GetExpansionPreferences() const
{
	return Preferences;
}
