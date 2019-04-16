// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/ResourceDeposit.h"
#include "Interfaces/MapGenerator.h"
#include "ScriptInterface.h"
#include "ResourceDepositGenerator.generated.h"

class UDataTable;
class ISpawnStrategy;
class IGridPlatform;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Deprecated)
class ARTILLERYSTRATEGY_API UDEPRECATED_ResourceDepositGenerator : public UActorComponent, public IMapGenerator
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDEPRECATED_ResourceDepositGenerator();

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
	TArray<FResourceHandle> AvailableDeposits;

	void CreateDeposits();
	FResourceHandle GetRandomResource() const;
	int32 GetRandomResourceAmount(const FResource& Resource) const;
	TScriptInterface<IGridPlatform> GetTileForDeposit() const;
};
