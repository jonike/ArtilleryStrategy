// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/OwnerController.h"
#include "Structs/ResourceDeposit.h"
#include "BaseGridPlatform.generated.h"

class UBoxComponent;
class UHierarchicalInstancedStaticMeshComponent;
class IBuilding;
class AInstancedMeshSpawner;

UCLASS()
class ARTILLERYSTRATEGY_API ABaseGridPlatform : public AActor, public IGridPlatform, public ICanBeOwned
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGridPlatform();

	// Called every frame
	void Tick(float DeltaTime) override;

	TScriptInterface<IOwnerController> GetOwnerController() const override;
	void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) override;
	bool HasOwnerController() const override;

	bool RequiresResourcesToOwn() const override;
	const FResourcePack& GetResourcesToOwn() const override;

	FVector GetBuildingSpawnLocation() const override;
	bool HasBuilding() const override;
	void SetBuilding(TScriptInterface<IBuilding> SpawnedBuilding) override;

	TSet<FResourceDeposit>& GetResourceDeposits() override;
	bool HasResourceDeposits() const override;
	void SetResourceDeposits(FResourceDeposit& Deposit) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	void NotifyActorOnClicked(FKey ButtonPressed) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = Buildings)
	FVector BuildingSpawnOffset;

	UPROPERTY(Category = "Resources", VisibleInstanceOnly)
	TSet<FResourceDeposit> ResourceDeposits;

	UPROPERTY(Category = "Resources", EditAnywhere)
	UBillboardComponent* ResourceBillboard;

	UPROPERTY(Category = "Resources", EditAnywhere)
	FResourcePack ResourcesToOwn;

	UPROPERTY(Category = "Visuals", EditDefaultsOnly)
	FVector InstancedMeshOffset;

	UPROPERTY(Category = "Visuals", VisibleInstanceOnly)
	int MeshInstanceIndex;

	TScriptInterface<IBuilding> Building;
	TScriptInterface<IOwnerController> OwnerController;

	UFUNCTION()
	void ReceiveOnClicked(AActor* TouchedActor, FKey ButtonPressed);

	void AddInstancedMesh();
	AInstancedMeshSpawner* GetInstancedMeshSpawner() const;
};
