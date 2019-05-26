// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionModifier.h"

float FActionModifier::GetCurrentValue() const
{
	if (EvaluateConditionTree())
	{
		return SuccessValue;
	}
	return FailureValue;
}

bool FActionModifier::EvaluateConditionTree() const
{
	return Condition && Condition->Evaluate();
}
