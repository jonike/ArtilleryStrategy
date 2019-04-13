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
	void SetupResourceWidget(const FName& Name, const FResource& Resource) override;

protected:
	UFUNCTION(Category = Initialization, BlueprintImplementableEvent)
	void FillResourceWidget(const FName& Name, const FResource& Resource);

	UFUNCTION(Category = "Update", BlueprintImplementableEvent, BlueprintCallable)
	void UpdateResourceAmount(const FResourceAmount& Resource);

	UFUNCTION(Category = "Resources", BlueprintPure)
	TScriptInterface<IWallet> GetWallet() const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	UResourceStorage* GetResourceStorage() const;

private:
	// TODO: FResource copied on on each initialization of widget (only once per widget, but still)
	FResource ShowedResource;

	UFUNCTION()
	void ReceiveOnResourceAdded(const FResourceAmount& Resource);
};
