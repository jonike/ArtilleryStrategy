// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AI/Controllers/DefaultAIController.h"
#include "Interfaces/FireManager.h"
#include "AdvancedAIController.generated.h"

class UExpansionPreferences;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API AAdvancedAIController : public ADefaultAIController, public IFireManager
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSignature);

public:
	AAdvancedAIController();

	FOnFireSignature OnFire;

	void AddToFireList(TScriptInterface<IWeaponBuilding> Weapon) override;

	UExpansionPreferences* GetExpansionPreferences() const;

private:
	UPROPERTY(EditAnywhere)
	UExpansionPreferences* Preferences;
};
