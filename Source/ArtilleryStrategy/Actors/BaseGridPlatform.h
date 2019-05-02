// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/PlayerProperty.h"
#include "Interfaces/OwnerController.h"
#include "Structs/ResourceDeposit.h"
#include "BaseGridPlatform.generated.h"

class UBoxComponent;
class UHierarchicalInstancedStaticMeshComponent;
class IBuilding;
class AInstancedMeshSpawner;

/**
 * \brief A base class for all tile classes
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseGridPlatform : public AActor, public IGridPlatform, public IPlayerProperty
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGridPlatform();

	TScriptInterface<IOwnerController> GetOwnerController() const override;
	void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) override;
	bool HasOwnerController() const override;

	bool RequiresResourcesToOwn() const override;
	const FResourcePack& GetResourcesToOwn() const override;

	FVector GetBuildingSpawnLocation() const override;
	bool HasBuilding() const override;
	void SetBuilding(TScriptInterface<IBuilding> SpawnedBuilding) override;
	TScriptInterface<IBuilding> CreateBuilding(TSubclassOf<AActor> BuildingClass) override;

	TSet<FResourceDeposit>& GetResourceDeposits() override;
	bool HasResourceDeposits() const override;
	void SetResourceDeposits(FResourceDeposit& Deposit) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	void NotifyActorOnClicked(FKey ButtonPressed) override;

private:
	/**
	 * \brief Component for collisions; root component of the actor
	 */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	UBoxComponent* CollisionBox;

	/**
	 * \brief Coordinates of the spawned building relative to tile
	 */
	UPROPERTY(EditAnywhere, Category = Buildings)
	FVector BuildingSpawnOffset;

	/**
	 * \brief List of resource deposits on the tile
	 */
	UPROPERTY(Category = "Resources", VisibleInstanceOnly)
	TSet<FResourceDeposit> ResourceDeposits;

	/**
	 * \brief Billboard that shows which resources are present on the tile
	 */
	UPROPERTY(Category = "Resources", EditAnywhere)
	UBillboardComponent* ResourceBillboard;

	/**
	 * \brief Billboard that shows which player owns the tile
	 */
	UPROPERTY(Category = "Ownership", EditAnywhere)
	UBillboardComponent* OwnerIconBillboard;

	/**
	 * \brief List of resource that player must spend in order to buy tile
	 */
	UPROPERTY(Category = "Resources", EditAnywhere)
	FResourcePack ResourcesToOwn;

	/**
	 * \brief Offset of the mesh that is created through HISM component
	 */
	UPROPERTY(Category = "Visuals", EditDefaultsOnly)
	FVector InstancedMeshOffset;

	/**
	 * \brief Index of instanced mesh in HISM component
	 */
	UPROPERTY(Category = "Visuals", VisibleInstanceOnly)
	int MeshInstanceIndex;

	/**
	 * \brief The buildings that is placed on the tile
	 */
	TScriptInterface<IBuilding> Building;

	/**
	 * \brief The player that owns this tile
	 */
	TScriptInterface<IOwnerController> OwnerController;

	/**
	 * \brief On actor being clicked with mouse
	 * \param TouchedActor The actor being touched (self)
	 * \param ButtonPressed Button pressed
	 */
	UFUNCTION()
	void ReceiveOnClicked(AActor* TouchedActor, FKey ButtonPressed);

	/**
	 * \brief Add instanced mesh using HISM component
	 */
	void AddInstancedMesh();

	/**
	 * \brief Create building actor and set it up
	 * \param BuildingClass Class of the building to spawn
	 * \return Pointer to the building actor
	 */
	AActor* SpawnBuildingActor(TSubclassOf<AActor> BuildingClass) const;

	/**
	 * \brief Finds actor that can use HISM to create instanced meshes
	 * \return Spawner, if found
	 */
	AInstancedMeshSpawner* GetInstancedMeshSpawner() const;
};
