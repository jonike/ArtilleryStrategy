// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/CanBeOwned.h"
#include "BuyPlatformWidget.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuyPlatformWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPropertyToBuy(TScriptInterface<ICanBeOwned> Property);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyClickedSignature, TScriptInterface<ICanBeOwned>, Property);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseClickedSignature);

	FOnBuyClickedSignature OnBuyClicked;
	FOnCloseClickedSignature OnCloseClicked;

protected:
	UFUNCTION(BlueprintCallable, Category = Buttons)
	void BuyCell() const;

	UFUNCTION(BlueprintCallable, Category = Buttons)
	void CloseBuyWidget() const;

private:
	TScriptInterface<ICanBeOwned> PropertyToBuy;
};
