// Fill out your copyright notice in the Description page of Project Settings.

#include "AgentLibrary.h"
#include "GameFramework/Actor.h"
#include "Brains/Brain.h"

TScriptInterface<IAgent> UAgentLibrary::GetAgent(const UBrain* Brain)
{
	check(Brain);
	return Brain->GetOuter();
}
