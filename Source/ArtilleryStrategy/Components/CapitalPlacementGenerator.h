// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/MapGenerator.h"
#include "CapitalPlacementGenerator.generated.h"

class ISpawnStrategy;
class IOwnerController;
class IBuilding;
class IGridPlatform;
class ACapitalBuilding;
class AController;
class ADefaultGS;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTILLERYSTRATEGY_API UCapitalPlacementGenerator : public UActorComponent, public IMapGenerator
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCapitalPlacementGenerator();

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

	UPROPERTY(EditAnywhere, Category = Capitals, meta = (MustImplement = "IBuilding"))
	TSubclassOf<ACapitalBuilding> CapitalActorClass;

	void PlaceCapitalsForAll() const;
	void PlaceCapital(TScriptInterface<IOwnerController> Controller) const;
	ACapitalBuilding* CreateCapitalBuilding(FVector Location) const;
	TScriptInterface<IGridPlatform> GetSpawnCell() const;
	void SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const;
};
