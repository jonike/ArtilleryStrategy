// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "Actors/InstancedMeshSpawner.h"
#include "DefaultGS.generated.h"

class UTurnProcessorComponent;
class IDEPRECATED_MapGenerator;
class IDEPRECATED_SpawnStrategy;
class UWorldGenerator;
class UTileMatrix;
class IWorldTile;

/**
 * \brief Base class for all game state classes
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADefaultGS();

	/**
	 * \brief Get turn processor component
	 * \return Turn processor component
	 */
	UFUNCTION(BlueprintCallable)
	UTurnProcessorComponent* GetTurnProcessor() const;

	/**
	 * \brief Get component that spawns tiles instanced meshes
	 * \return Component for spawning instanced meshes for tiles
	 */
	UFUNCTION(BlueprintCallable)
	AInstancedMeshSpawner* GetTileMeshSpawner() const;

	/**
	 * \brief Get world generator
	 * \return Component that generates game world
	 */
	UFUNCTION(BlueprintCallable)
	UWorldGenerator* GetWorldGenerator() const;

protected:
	void PostInitializeComponents() override;
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Generation", EditAnywhere)
	UWorldGenerator* WorldGenerator;

	UPROPERTY(Category = "Turns", EditAnywhere)
	UTurnProcessorComponent* TurnProcessorComponent;

	UPROPERTY()
	AInstancedMeshSpawner* TileMeshSpawner;

	UPROPERTY(Category = "Instanced meshes", EditDefaultsOnly)
	TSubclassOf<AInstancedMeshSpawner> InstancedMeshSpawnerClass;
};
