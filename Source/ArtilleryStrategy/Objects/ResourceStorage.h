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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceAddedSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResourceSpentSignature);

public:
	// TODO: replace FResourceDeposit with FResourceAmount?
	UFUNCTION(Category = "Resources", BlueprintCallable)
	void AddResource(FResourceAmount& Resource);

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void SpendResource(FResourceAmount& Resource);

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmount(FResource& Resource) const;

	UFUNCTION(Category = "Resources", BlueprintPure)
	bool IsEnough(FResourceAmount& Resource) const;

	FOnResourceAddedSignature OnResourceAdded;
	FOnResourceSpentSignature OnResourceSpent;

private:
	// TODO: replace with separate class/struct
	UPROPERTY(EditAnywhere)
	TMap<FResource, int> Storage;
};
