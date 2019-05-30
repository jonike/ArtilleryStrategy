// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Conditions/Unary.h"
#include "Not.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UNot : public UUnary
{
	GENERATED_BODY()

protected:
	bool EvaluateOne(bool Result) const override;
};
