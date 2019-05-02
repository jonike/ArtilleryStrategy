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

TScriptInterface<IFireManager> UASLibrary::GetFireManagerForActor(AActor* Actor)
{
	check(Actor);
	return Actor->GetInstigatorController();
}

TScriptInterface<IFireManager> UASLibrary::GetFireManagerForPawn(APawn* Pawn)
{
	check(Pawn);
	return Pawn->GetController();
}

UWorldGenerator* UASLibrary::GetMapGenerator(UObject* Object)
{
	check(Object);
	const auto World = Object->GetWorld();
	check(World);
	const auto GameState = World->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetWorldGenerator();
}

TScriptInterface<IPlayerRepository> UASLibrary::GetPlayerRepositoryForActor(AActor* Actor)
{
	check(Actor);
	const auto Controller = Actor->GetInstigatorController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}

TScriptInterface<IPlayerRepository> UASLibrary::GetPlayerRepositoryForPawn(APawn* Pawn)
{
	check(Pawn);
	const auto Controller = Pawn->GetController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}

const FWorldParams& UASLibrary::GetWorldParams(UObject* Object)
{
	const auto MapGenerator = GetMapGenerator(Object);
	check(MapGenerator);
	return MapGenerator->GetWorldParams();
}

const FPlayerTurnLimits& UASLibrary::GetPlayerTurnLimitsForController(AController* Controller)
{
	const auto State = Controller->GetPlayerState<ADefaultPlayerState>();
	check(State);
	return State->GetTurnLimits();
}
