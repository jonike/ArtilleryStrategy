// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "ResourceStorage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourceStorage
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Add(const FName& Resource, const double Amount) { Storage[Resource] += Amount; }

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Spend(const FName& Resource, const double Amount) { Storage[Resource] -= Amount; }

	UFUNCTION(Category = "Resources", BlueprintPure)
	auto GetAmount(const FName& Resource) const { return Storage[Resource]; }

	UFUNCTION(Category = "Resources", BlueprintPure)
	bool IsEnough(const FName& Resource, const double Amount) const { return GetAmount(Resource) >= Amount; }

private:
	UPROPERTY(EditAnywhere)
	TMap<FName, double> Storage;
};
