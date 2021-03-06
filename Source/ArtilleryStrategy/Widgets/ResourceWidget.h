// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ResourceWidgetInterface.h"
#include "Interfaces/PlayerRepository.h"
#include "Structs/ResourceHandle.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceWidget : public UUserWidget, public IResourceWidgetInterface
{
	GENERATED_BODY()

public:
	void SetupResourceWidget(FResourceHandle Resource) override;

protected:
	UFUNCTION(Category = Initialization, BlueprintImplementableEvent)
	void FillResourceWidget(FResourceHandle Resource);

	UFUNCTION(Category = "Update", BlueprintImplementableEvent, BlueprintCallable)
	void UpdateResourceAmount(const FResourceAmount& Resource);

	UFUNCTION(Category = "Resources", BlueprintPure)
	TScriptInterface<IPlayerRepository> GetWallet() const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	UResourceStorage* GetResourceStorage() const;

private:
	FResourceHandle ShowedResource;

	UFUNCTION()
	void ReceiveOnResourceAmountChanged(const FResourceAmount& Resource);
};
