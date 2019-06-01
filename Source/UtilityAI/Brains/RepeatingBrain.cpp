// Fill out your copyright notice in the Description page of Project Settings.

#include "RepeatingBrain.h"
#include "Engine/World.h"
#include "TimerManager.h"

void URepeatingBrain::Initialize(const TScriptInterface<IAgent> Instigator)
{
	Super::Initialize(Instigator);
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &UBrain::Run, Step, true, -1.0);
}

void URepeatingBrain::Stop()
{
	if (Timer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}

void URepeatingBrain::BeginDestroy()
{
	Stop();
	Super::BeginDestroy();
}
