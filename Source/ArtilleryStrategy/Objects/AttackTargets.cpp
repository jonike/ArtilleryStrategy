// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTargets.h"

void UAttackTargets::Add(AActor* Target)
{
	Targets.Add(Target);
}

const TSet<AActor*>& UAttackTargets::GetTargets() const
{
	return Targets;
}
