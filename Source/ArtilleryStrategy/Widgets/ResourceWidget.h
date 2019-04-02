// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ResourceWidgetInterface.h"
#include "Interfaces/Wallet.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceWidget : public UUserWidget, public IResourceWidgetInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = Initialization, BlueprintImplementableEvent)
	void Fill(const FName& Name, const FResource& Resource) override;

protected:
	UFUNCTION(Category = "Resources", BlueprintPure)
	TScriptInterface<IWallet> GetWallet() const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	UResourceStorage* GetResourceStorage() const;
};
