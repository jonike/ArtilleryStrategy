// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Wallet.h"
#include "DefaultPlayerState.generated.h"

class UResourceBuildingsManager;
class UResourceStorage;
/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerState : public APlayerState, public IWallet
{
	GENERATED_BODY()

public:
	ADefaultPlayerState();

	UFUNCTION(Category = "Wallet", BlueprintPure)
	UResourceStorage* GetResourceWallet() const override { return Storage; }

	auto GetResourceBuildingsManager() const { return ResourceBuildingsManager; }

private:
	UPROPERTY(Category = "Resources", EditAnywhere)
	UResourceStorage* Storage;

	UPROPERTY(Category = "Resources|Buildings", VisibleInstanceOnly)
	UResourceBuildingsManager* ResourceBuildingsManager;
};
