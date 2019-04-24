// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnDependent.h"
#include "Engine/World.h"
#include "Game/States/DefaultGS.h"

void ITurnDependent::ReceiveOnTurnStarted()
{
}

void ITurnDependent::ReceiveOnTurnEnded()
{
}

// Add default functionality here for any ITurnDependent functions that are not pure virtual.
UTurnProcessorComponent* ITurnDependent::GetTurnProcessor(const UObject* Context) const
{
	const auto GameState = Context->GetWorld()->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetTurnProcessor();
}
