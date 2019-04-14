// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Wallet.h"
#include "ResourceStorageWidget.generated.h"

class IResourceWidgetInterface;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceStorageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

protected:
	UFUNCTION(Category = Resources, BlueprintImplementableEvent)
	void PlaceResourceWidget(UUserWidget* ResourceWidget);

private:
	UPROPERTY(Category = Resources, EditDefaultsOnly)
	TSet<FResourceHandle> ResourcesToShow;

	UPROPERTY(Category = Widgets, EditAnywhere, meta = (MustImplement = "ResourceWidgetInterface"))
	TSubclassOf<UUserWidget> ResourceWidgetClass;

	TArray<TScriptInterface<IResourceWidgetInterface>> ResourceWidgets;

	TScriptInterface<IResourceWidgetInterface> GetResourceWidget(int Index);
	TScriptInterface<IWallet> GetWallet() const;
};
