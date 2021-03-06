// Fill out your copyright notice in the Description page of Project Settings.

#include "Brain.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Actions/Action.h"
#include "Agents/Agent.h"
#include "Libraries/AgentLibrary.h"

void UBrain::Initialize(const TScriptInterface<IAgent> Instigator)
{
	check(Instigator);
	Agent = Instigator;
}

UAction* UBrain::SelectAction() const
{
	if (Actions.Num() == 0)
	{
		return nullptr;
	}
	auto SelectedAction = Actions[0];
	auto CurrentValue = 0.f;
	for (const auto Action : Actions)
	{
		const auto Value = Action->Evaluate();
		if (Value >= AutoSelectThreshold)
		{
			return Action;
		}
		if (Value > CurrentValue)
		{
			SelectedAction = Action;
			CurrentValue = Value;
		}
	}
	return SelectedAction;
}

TScriptInterface<IAgent> UBrain::GetAgent() const
{
	check(Agent);
	return Agent;
}

float UBrain::GetAutoSelectThreshold() const
{
	return AutoSelectThreshold;
}

void UBrain::Run() const
{
	if (const auto Action = SelectAction())
	{
		Action->Run(GetAgent());
	}
}

const TArray<UAction*>& UBrain::GetActions() const
{
	return Actions;
}
