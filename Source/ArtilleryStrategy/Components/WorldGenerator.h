// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Structs/WorldParams.h"
#include "Interfaces/WorldGenerationPass.h"
#include "ScriptInterface.h"
#include "WorldGenerator.generated.h"

class IWorldTile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTILLERYSTRATEGY_API UWorldGenerator : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldGenerationStartSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldGenerationEndSignature);

public:
	// Sets default values for this component's properties
	UWorldGenerator();

	FOnWorldGenerationStartSignature OnWorldGenerationStart;
	FOnWorldGenerationEndSignature OnWorldGenerationEnd;

	void GenerateWorld();

	const FWorldParams& GetWorldParams() const;

protected:
	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Category = "World generation", EditAnywhere)
	int Rows = 20;

	UPROPERTY(Category = "World generation", EditAnywhere)
	int Columns = 20;

	UPROPERTY(Category = "World generation", EditAnywhere)
	FWorldParams WorldParams;

	UPROPERTY(Category = "World generation", EditAnywhere)
	TArray<TScriptInterface<IWorldGenerationPass>> WorldGenerationPasses;
};
