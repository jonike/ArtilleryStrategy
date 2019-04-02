// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/Wallet.h"
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
	const FResourceStorage& GetResourceWallet() const override { return Storage; }

private:
	UPROPERTY(EditAnywhere, Category = Resources)
	int Money = 1000;

	UPROPERTY(Category = Resources, EditAnywhere)
	FResourceStorage Storage;
};
