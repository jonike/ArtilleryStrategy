// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Conditions/Binary.h"
#include "And.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UAnd : public UBinary
{
	GENERATED_BODY()

protected:
	bool EvaluateTwo(bool FirstResult, bool SecondResult) const override;
};
