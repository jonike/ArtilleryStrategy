// Fill out your copyright notice in the Description page of Project Settings.


#include "AtLeastOne.h"

bool UAtLeastOne::ProcessValuePair(const bool Current, const bool NextValue) const
{
	return Current || NextValue;
}

bool UAtLeastOne::GetInitialValue() const
{
	return false;
}
