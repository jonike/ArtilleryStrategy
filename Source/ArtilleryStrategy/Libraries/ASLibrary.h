// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Structs/PlayerTurnLimits.h"
#include "Structs/WorldParams.h"
#include "ASLibrary.generated.h"

class AController;
class IWallet;
class IOwnerController;
class UGridGenerator;
class IFireManager;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UASLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IFireManager> GetFireManagerForActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IFireManager> GetFireManagerForPawn(APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	static UGridGenerator* GetMapGenerator(UObject* Object);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IWallet> GetWalletForActor(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static TScriptInterface<IWallet> GetWalletForPawn(APawn* Pawn);

	UFUNCTION(BlueprintCallable)
	static const FWorldParams& GetWorldParams(UObject* Object);

	UFUNCTION(BlueprintCallable)
	static const FPlayerTurnLimits& GetPlayerTurnLimitsForController(AController* Controller);
};
