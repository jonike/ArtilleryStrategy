// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ValueLimit.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FValueLimit
{
	GENERATED_BODY()

public:
	FValueLimit() = default;
	explicit FValueLimit(int MaxValue);
	FValueLimit(int Value, int MaxValue);

	void Increment();
	void Reset();

	bool IsLimitReached() const;

private:
	int Value = 0;
	int MaxValue = 1;
};
