// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CapitalPlacementGenerator.generated.h"

class IOwnerController;
class IBuilding;
class IGridPlatform;
class ACapitalBuilding;
class AController;
class ADefaultGS;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTILLERYSTRATEGY_API UCapitalPlacementGenerator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCapitalPlacementGenerator();

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void PlaceCapitalsForAll() const;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Capitals, meta = (MustImplement = "IBuilding"))
	TSubclassOf<ACapitalBuilding> CapitalActorClass;

	void PlaceCapital(TScriptInterface<IOwnerController> Controller) const;
	ACapitalBuilding* CreateCapitalBuilding(FVector Location) const;
	TScriptInterface<IGridPlatform> GetSpawnCell() const;
	void SetupCapitalBuilding(ACapitalBuilding* Capital, TScriptInterface<IOwnerController> Controller) const;
};
