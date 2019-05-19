// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structs/PlayerTurnLimits.h"
#include "Structs/WorldParams.h"
#include "ASLibrary.generated.h"

class AController;
class IPlayerRepository;
class IOwnerController;
class UWorldGenerator;
class IFireManager;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UCoreLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IFireManager> GetFireManagerForActor(const AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IFireManager> GetFireManagerForPawn(const APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	static UWorldGenerator* GetMapGenerator(const UObject* Object);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IPlayerRepository> GetPlayerRepositoryForActor(const AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IPlayerRepository> GetPlayerRepositoryForPawn(const APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	static const FWorldParams& GetWorldParams(const UObject* Object);

	UFUNCTION(BlueprintCallable)
	static const FPlayerTurnLimits& GetPlayerTurnLimitsForController(const AController* Controller);
};
