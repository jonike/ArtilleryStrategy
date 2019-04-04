// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structs/Resource.h"
#include "ResourceDeposit.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceDeposit : public UObject
{
	GENERATED_BODY()

public:
	int GetAmount() const;
	const FResource* GetResource() const;
	FName GetResourceName() const;

private:
	UPROPERTY(Category = "Resource", EditAnywhere)
	FName ResourceName;

	UPROPERTY(Category = "Resource", EditDefaultsOnly)
	UDataTable* ResourceDepositTable;

	UPROPERTY(Category = "Resource", EditAnywhere)
	int Amount;
};
