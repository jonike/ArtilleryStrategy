// Fill out your copyright notice in the Description page of Project Settings.


#include "ASLibrary.h"
#include "Interfaces/FireManager.h"
#include "Interfaces/PlayerRepository.h"
#include "Engine/World.h"
#include "Game/States/DefaultGS.h"
#include "ScriptInterface.h"
#include "GameFramework/PlayerState.h"
#include "Components/WorldGenerator.h"
#include "Player/States/DefaultPlayerState.h"

TScriptInterface<IFireManager> UASLibrary::GetFireManagerForActor(const AActor* Actor)
{
	check(Actor);
	return Actor->GetInstigatorController();
}

TScriptInterface<IFireManager> UASLibrary::GetFireManagerForPawn(const APawn* Pawn)
{
	check(Pawn);
	return Pawn->GetController();
}

UWorldGenerator* UASLibrary::GetMapGenerator(const UObject* Object)
{
	check(Object);
	const auto World = Object->GetWorld();
	check(World);
	const auto GameState = World->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetWorldGenerator();
}

TScriptInterface<IPlayerRepository> UASLibrary::GetPlayerRepositoryForActor(const AActor* Actor)
{
	check(Actor);
	const auto Controller = Actor->GetInstigatorController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}

TScriptInterface<IPlayerRepository> UASLibrary::GetPlayerRepositoryForPawn(const APawn* Pawn)
{
	check(Pawn);
	const auto Controller = Pawn->GetController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}

const FWorldParams& UASLibrary::GetWorldParams(const UObject* Object)
{
	const auto MapGenerator = GetMapGenerator(Object);
	check(MapGenerator);
	return MapGenerator->GetWorldParams();
}

const FPlayerTurnLimits& UASLibrary::GetPlayerTurnLimitsForController(const AController* Controller)
{
	const auto State = Controller->GetPlayerState<ADefaultPlayerState>();
	check(State);
	return State->GetTurnLimits();
}
