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
	bool IsEnoughMoney(int Amount) const override;
	void AddMoney(int Amount) override;
	void RemoveMoney(int Amount) override;
	int GetMoneyAmount() const override;

private:
	UPROPERTY(EditAnywhere, Category = Resources)
		int Money = 1000;
};
