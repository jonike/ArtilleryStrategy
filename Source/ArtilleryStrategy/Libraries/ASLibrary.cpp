// Fill out your copyright notice in the Description page of Project Settings.


#include "ASLibrary.h"
#include "Interfaces/FireManager.h"
#include "Interfaces/Wallet.h"
#include "Engine/World.h"
#include "Game/States/DefaultGS.h"
#include "ScriptInterface.h"
#include "GameFramework/PlayerState.h"

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

UGridGenerator* UASLibrary::GetMapGenerator(UObject* Object)
{
	check(Object);
	const auto World = Object->GetWorld();
	check(World);
	const auto GameState = World->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetGridGenerator();
}

TScriptInterface<IWallet> UASLibrary::GetWalletForActor(AActor* Actor)
{
	check(Actor);
	const auto Controller = Actor->GetInstigatorController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}

TScriptInterface<IWallet> UASLibrary::GetWalletForPawn(APawn* Pawn)
{
	check(Pawn);
	const auto Controller = Pawn->GetController();
	check(Controller);
	return Controller->GetPlayerState<APlayerState>();
}
