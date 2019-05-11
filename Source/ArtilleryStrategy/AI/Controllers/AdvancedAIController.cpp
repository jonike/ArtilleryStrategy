// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedAIController.h"
#include "Objects/ExpansionPreferences.h"

AAdvancedAIController::AAdvancedAIController()
{
	Preferences = CreateDefaultSubobject<UExpansionPreferences>(TEXT("Expansion preferences"));
}

UExpansionPreferences* AAdvancedAIController::GetExpansionPreferences() const
{
	return Preferences;
}
