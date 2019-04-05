// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/ResourceDeposit.h"
#include "Interfaces/MapGenerator.h"
#include "ResourceDepositGenerator.generated.h"

class ISpawnStrategy;
class IGridPlatform;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARTILLERYSTRATEGY_API UResourceDepositGenerator : public UActorComponent, public IMapGenerator
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UResourceDepositGenerator();

protected:
	UFUNCTION()
	void ReceiveOnGridGenerationEnded(UTileMatrix* Tiles) override;

	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeComponent() override;

private:
	UPROPERTY(Category = "Procedural generation", EditDefaultsOnly, meta = (MustImplement = "SpawnStrategy"))
	TSubclassOf<UObject> SpawnStrategyClass;
	UPROPERTY()
	TScriptInterface<ISpawnStrategy> SpawnStrategy;

	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	int DepositsAmount = 4;

	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	TSet<UResourceDeposit*> AvailableDeposits;

	void CreateDeposits();

	TScriptInterface<IGridPlatform> GetTileForDeposit() const;
};
