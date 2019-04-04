// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ResourceDeposit.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceDeposit : public UObject
{
	GENERATED_BODY()

public:
	int GetAmount() const;

private:
	UPROPERTY(Category = "Resource", EditAnywhere)
	int Amount;
};
