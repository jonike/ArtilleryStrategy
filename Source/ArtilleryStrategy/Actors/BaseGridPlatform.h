// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/OwnerController.h"
#include "BaseGridPlatform.generated.h"

class UResourceDeposit;
class IBuilding;

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
	int GetCost() const override;

	FVector GetBuildingSpawnLocation() const override;
	bool HasBuilding() const override;
	void SetBuilding(TScriptInterface<IBuilding> SpawnedBuilding) override;

	UResourceDeposit* GetResourceDeposit() const override;
	bool HasResourceDeposit() const override;
	void SetResourceDeposit(UResourceDeposit* Deposit) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	void NotifyActorOnClicked(FKey ButtonPressed) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = Cost)
	int Cost = 50;

	UPROPERTY(EditAnywhere, Category = Buildings)
	FVector BuildingSpawnOffset;

	UPROPERTY(Category = "Resources", VisibleAnywhere)
	UResourceDeposit* ResourceDeposit;

	UPROPERTY(Category = "Resources|Visuals", EditAnywhere)
	UBillboardComponent* ResourceBillboard;

	TScriptInterface<IBuilding> Building;
	TScriptInterface<IOwnerController> OwnerController;

	UFUNCTION()
	void ReceiveOnClicked(AActor* TouchedActor, FKey ButtonPressed);
};
