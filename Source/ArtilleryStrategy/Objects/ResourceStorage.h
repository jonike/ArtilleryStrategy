// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Resource.h"
#include "Structs/ResourceDeposit.h"
#include "ResourceStorage.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced)
class ARTILLERYSTRATEGY_API UResourceStorage : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceAddedSignature, const FResourceAmount&, ResourceAmount);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnResourceSpentSignature, const FResourceAmount&, ResourceAmount);

public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
	void AddResource(FResourceAmount ResourceAmount);

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void SpendResource(FResourceAmount ResourceAmount);

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmount(const FResource& Resource) const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	bool IsEnough(const FResourceAmount& Resource) const;

	FOnResourceAddedSignature OnResourceAdded;
	FOnResourceSpentSignature OnResourceSpent;

private:
	UPROPERTY(EditAnywhere)
	TMap<FResource, int> Storage;
};
