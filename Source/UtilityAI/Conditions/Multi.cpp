// Fill out your copyright notice in the Description page of Project Settings.


#include "Multi.h"

bool UMulti::ProcessValuePair(bool Current, bool NextValue) const
{
	return false;
}

bool UMulti::GetInitialValue() const
{
	return false;
}

bool UMulti::EvaluateRaw() const
{
	auto Result = GetInitialValue();
	for (const auto Condition : Conditions)
	{
		Result = ProcessValuePair(Result, Condition && Condition->Evaluate());
	}
	return Result;
}
