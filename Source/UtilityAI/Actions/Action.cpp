// Fill out your copyright notice in the Description page of Project Settings.

#include "Action.h"
#include "Agents/Agent.h"
#include "Tasks/Task.h"

float UAction::Evaluate() const
{
	return FMath::Clamp(EvaluateRaw(), 0.f, 1.f);
}

void UAction::Run(TScriptInterface<IAgent> Agent)
{
	for (const auto& Task : Tasks)
	{
		Task->Run(Agent);
	}
}

float UAction::EvaluateRaw() const
{
	auto Value = 0.f;
	for (const auto& Condition : Modifiers)
	{
		Value += Condition.GetCurrentValue();
	}
	return Value;
}
