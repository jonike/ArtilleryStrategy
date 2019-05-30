// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Multi.h"
#include "All.generated.h"

/**
 * 
 */
UCLASS()
class UTILITYAI_API UAll : public UMulti
{
	GENERATED_BODY()

protected:
	bool ProcessValuePair(bool Current, bool NextValue) const override;
	bool GetInitialValue() const override;
};
