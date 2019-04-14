// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/ResourceDeposit.h"
#include "Structs/ResourceHandle.h"
#include "Structs/ResourcePack.h"
#include "ResourceStorage.generated.h"

struct FResourcePack;
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
	void AddResourcePack(const FResourcePack& ResourcePack);

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void SpendResource(FResourceAmount ResourceAmount);

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void SpendResourcePack(const FResourcePack& ResourcePack);

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmount(const FResourceHandle& Resource) const;

	UFUNCTION(Category = "Resources", BlueprintPure, meta = (DisplayName = "IsEnough (Single resource)"))
	bool IsEnough(const FResourceAmount& Resource) const;

	UFUNCTION(Category = "Resources", BlueprintCallable, meta = (DisplayName = "IsEnough (Pack)"))
	bool IsEnoughPack(const FResourcePack& ResourcePack) const;

	FOnResourceAddedSignature OnResourceAdded;
	FOnResourceSpentSignature OnResourceSpent;

private:
	UPROPERTY(EditAnywhere)
	TMap<FResourceHandle, int> Storage;
};
