// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/WorldParams.h"
#include "Interfaces/LandscapeGenerationStrategy.h"
#include "ScriptInterface.h"
#include "WorldGenerator.generated.h"

class IGridPlatform;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTILLERYSTRATEGY_API UGridGenerator : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldGenerationStartSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldGenerationEndSignature);

public:
	// Sets default values for this component's properties
	UGridGenerator();

	void GenerateWorld() const;

	FOnWorldGenerationStartSignature OnWorldGenerationStart;
	FOnWorldGenerationEndSignature OnWorldGenerationEnd;

protected:
	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Category = "World generation", EditAnywhere)
	FWorldParams WorldParams;

	UPROPERTY(Category = "World generation", EditAnywhere)
	TArray<TScriptInterface<ILandscapeGenerationStrategy>> WorldGenerationPasses;
};
