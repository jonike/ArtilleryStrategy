// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Conditions/Binary.h"
#include "Xor.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UXor : public UBinary
{
	GENERATED_BODY()

protected:
	bool EvaluateTwo(bool FirstResult, bool SecondResult) const override;
};
