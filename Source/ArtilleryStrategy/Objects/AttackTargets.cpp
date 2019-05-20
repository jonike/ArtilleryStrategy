// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackTargets.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PlayerProperty.h"

void UAttackTargets::Add(AActor* Target)
{
	if (Target == nullptr || Target->IsPendingKill())
	{
		return;
	}
	if (const auto Property = Cast<IPlayerProperty>(Target))
	{
		// TODO: comparison may not work in future
		if (Property->GetOwnerController().GetObject() == GetOuter())
		{
			return;
		}
	}
	Targets.Add(Target);
}

const TArray<AActor*>& UAttackTargets::GetTargets()
{
	Targets.Remove(nullptr);
	return Targets;
}
