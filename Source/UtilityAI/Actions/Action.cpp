// Fill out your copyright notice in the Description page of Project Settings.

#include "Action.h"

float UAction::Evaluate() const
{
	return FMath::Clamp(EvaluateRaw(), 0.f, 1.f);
}

float UAction::EvaluateRaw() const
{
	auto Value = 0.f;
	for (const auto& Condition : Conditions)
	{
		Value += Condition.GetCurrentValue();
	}
	return Value;
}
