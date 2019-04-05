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
UCLASS(BlueprintType, Blueprintable)
class ARTILLERYSTRATEGY_API UResourceDeposit : public UObject
{
	GENERATED_BODY()

public:
	int GetAmount() const;
	FResource GetResource() const;
	void Setup(FResource* Resource, int Amount);

private:
	UPROPERTY(Category = "Resource", EditAnywhere)
	FResource Resource;

	UPROPERTY(Category = "Resource", EditAnywhere)
	int Amount;
};
