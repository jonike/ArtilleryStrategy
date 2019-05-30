// Fill out your copyright notice in the Description page of Project Settings.


#include "All.h"

bool UAll::ProcessValuePair(const bool Current, const bool NextValue) const
{
	return Current && NextValue;
}

bool UAll::GetInitialValue() const
{
	return true;
}
