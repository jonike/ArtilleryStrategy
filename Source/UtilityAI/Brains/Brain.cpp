// Fill out your copyright notice in the Description page of Project Settings.


#include "Brain.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Actions/Action.h"
#include "Agents/Agent.h"
#include "Libraries/AgentLibrary.h"

void UBrain::Start()
{
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UBrain::Act, Step, true, -1.0);
}

void UBrain::Stop()
{
	if (Timer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
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

float UBrain::GetAutoSelectThreshold() const
{
	return AutoSelectThreshold;
}

TScriptInterface<IAgent> UBrain::GetAgent() const
{
	return UAgentLibrary::GetAgent(this);
}

void UBrain::Act() const
{
	const auto Agent = GetAgent();
	check(Agent);
	if (const auto Action = SelectAction())
	{
		Agent->Act(Action);
	}
}

const TArray<UAction*>& UBrain::GetActions() const
{
	return Actions;
}
