// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Resource.h"
#include "ResourceStorage.generated.h"

class UResourceDeposit;

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced)
class ARTILLERYSTRATEGY_API UResourceStorage : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAddedSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceSpentSignature);

public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Add(UResourceDeposit* Resource);

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Spend(UResourceDeposit* Resource, float Amount);

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmount(UResourceDeposit* Resource) const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmountByName(FName Resource) const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	bool IsEnough(UResourceDeposit* Resource, float Amount) const;

	FOnResourceAddedSignature OnResourceAdded;
	FOnResourceSpentSignature OnResourceSpent;

private:
	UPROPERTY(EditAnywhere)
	TMap<FName, UResourceDeposit*> Storage;
};
