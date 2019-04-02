// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/Resource.h"
#include "ResourceStorage.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ARTILLERYSTRATEGY_API UResourceStorage : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Add(const FName& Resource, const float Amount) { Storage[Resource] += Amount; }

	UFUNCTION(Category = "Resources", BlueprintCallable)
	void Spend(const FName& Resource, const float Amount) { Storage[Resource] -= Amount; }

	UFUNCTION(Category = "Resources", BlueprintPure)
	float GetAmount(const FName& Resource) const { return Storage[Resource]; }

	UFUNCTION(Category = "Resources", BlueprintPure)
	bool IsEnough(const FName& Resource, const float Amount) const { return GetAmount(Resource) >= Amount; }

private:
	UPROPERTY(EditAnywhere)
	TMap<FName, float> Storage;
};
