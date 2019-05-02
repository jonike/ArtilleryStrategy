// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Interfaces/Building.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/TurnDependent.h"
#include "BaseBuilding.generated.h"

/**
 * \brief Base class for all buildings
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseBuilding : public AActor, public IBuilding, public ICanBeOwned, public ITurnDependent
{
	GENERATED_BODY()

public:
	ABaseBuilding();

	UFUNCTION()
	void ReceiveOnTurnEnded() override;

	auto GetOwnerController() const -> TScriptInterface<IOwnerController> override;
	auto SetOwnerController(TScriptInterface<IOwnerController> NewOwner) -> void override;
	auto HasOwnerController() const -> bool override;

	auto RequiresResourcesToOwn() const -> bool override;
	auto GetResourcesToOwn() const -> const FResourcePack& override;

	auto PostPlaced(TScriptInterface<IGridPlatform> Tile) -> void override;
	auto PrePlaced(TScriptInterface<IGridPlatform> Tile) -> void override;

protected:
	// Called when the game starts or when spawned
	auto BeginPlay() -> void override;

	// Called every frame
	auto Tick(float DeltaTime) -> void override;

	auto TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) -> float override;

private:
	/**
	 * \brief Static mesh component - visible part of building actor
	 */
	UPROPERTY(Category = Visuals, EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	/**
	 * \brief Amount of damage the actor can absorb before destruction
	 */
	UPROPERTY(Category = Health, EditAnywhere)
	float Health = 200.f;

	/**
	 * \brief Resources that are required to own this building
	 */
	UPROPERTY(Category = "Resources", EditAnywhere)
	FResourcePack ResourcesToOwn;

	/**
	 * \brief A controller that owns this object
	 */
	TScriptInterface<IOwnerController> OwnerController;

	/**
	 * \brief The tile this building was built on
	 */
	TScriptInterface<IGridPlatform> UnderlyingTile;
};
