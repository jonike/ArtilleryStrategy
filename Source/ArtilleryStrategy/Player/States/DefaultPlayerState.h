// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Wallet.h"
#include "Objects/ResourceStorage.h"
#include "DefaultPlayerState.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerState : public APlayerState, public IWallet
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Wallet", BlueprintPure)
	UResourceStorage* GetResourceWallet() const override { return Storage; }

protected:
	void PostInitializeComponents() override;

private:
	UPROPERTY(EditAnywhere, Category = Resources)
	int Money = 1000;

	UPROPERTY(Category = Resources, EditAnywhere)
	UResourceStorage* Storage;
};
