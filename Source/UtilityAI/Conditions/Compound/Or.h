// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Binary.h"
#include "Or.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UOr : public UBinary
{
	GENERATED_BODY()

protected:
	bool EvaluateTwo(bool FirstResult, bool SecondResult) const override;
};
