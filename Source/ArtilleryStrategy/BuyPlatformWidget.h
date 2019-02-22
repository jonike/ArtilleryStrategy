// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuyPlatformWidget.generated.h"

class ICanBuyCells;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuyPlatformWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = Buttons)
		void BuyCell() const;

	UFUNCTION(BlueprintCallable, Category = Buttons)
		void CloseBuyWidget() const;

private:
	ICanBuyCells* GetBuyer() const;
};
