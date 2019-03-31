// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Wallet.h"
#include "ResourceStorageWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceStorageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

private:
	UPROPERTY(Category = Resources, EditAnywhere)
	UDataTable* ResourcesTable;

	TScriptInterface<IWallet> GetWallet() const;
};
