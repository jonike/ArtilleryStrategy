// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InstancedMeshSpawner.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
/**
 * \brief An actor for spawning instanced meshes
 */
UCLASS()
class ARTILLERYSTRATEGY_API AInstancedMeshSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInstancedMeshSpawner();

	/**
	 * \brief Get HISM component for spawning instanced meshes
	 * \return HISM component that can spawn instanced meshes
	 */
	auto GetTileInstancedMesh() const -> UHierarchicalInstancedStaticMeshComponent*;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:
	/**
	 * \brief HISM component that can spawn instanced meshes
	 */
	UPROPERTY(Category = "Tiles", EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* TileInstancedMesh;
};
