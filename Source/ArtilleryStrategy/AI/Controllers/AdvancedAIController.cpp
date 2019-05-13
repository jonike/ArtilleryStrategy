// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedAIController.h"
#include "Objects/ExpansionPreferences.h"
#include "Actors/BaseWeaponBuilding.h"

AAdvancedAIController::AAdvancedAIController()
{
	Preferences = CreateDefaultSubobject<UExpansionPreferences>(TEXT("Expansion preferences"));
}

void AAdvancedAIController::AddToFireList(const TScriptInterface<IWeaponBuilding> Weapon)
{
	// TODO: remove cast to class
	const auto WeaponBuilding = Cast<ABaseWeaponBuilding>(Weapon.GetObject());
	check(WeaponBuilding);
	OnFire.AddDynamic(WeaponBuilding, &ABaseWeaponBuilding::Fire);
}

UExpansionPreferences* AAdvancedAIController::GetExpansionPreferences() const
{
	return Preferences;
}
