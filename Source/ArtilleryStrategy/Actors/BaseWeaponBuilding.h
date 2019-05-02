// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/WeaponBuilding.h"
#include "BaseWeaponBuilding.generated.h"

class IFireManager;

/**
 * \breaf A base class for all weapon buildings
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseWeaponBuilding : public ABaseBuilding, public IWeaponBuilding
{
	GENERATED_BODY()

public:
	ABaseWeaponBuilding();

	UFUNCTION()
	void Fire() override;

	void SetPlaneAngle(float Angle) override;
	void SetHorizonAngle(float Angle) override;

	bool IsReadyForFire() const override;

protected:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void PostPlaced(TScriptInterface<IWorldTile> Tile) override;
	void ReceiveOnTurnStarted() override;
	void ReceiveOnTurnEnded() override;

private:
	/**
	 * \brief A class of projectile being used
	 */
	UPROPERTY(Category = Projectile, EditAnywhere, meta = (MustImplement = "Projectile"))
	TSubclassOf<AActor> ProjectileClass;

	/**
	 * \brief The impulse which is used to launch projectile
	 */
	UPROPERTY(Category = Projectile, EditAnywhere)
	float ProjectileImpulse = 200.F;

	/**
	 * \brief Min vertical angle to shoot
	 */
	UPROPERTY(Category = Shooting, EditAnywhere)
	float MinShootAngle = 0.f;

	/**
	 * \brief Max vertical angle to shoot
	 */
	UPROPERTY(Category = Shooting, EditAnywhere)
	float MaxShootAngle = 60.f;

	/**
	 * \brief A value that is used to calculate gun angle from distance to the player mouse cursor
	 */
	UPROPERTY(Category = Shooting, EditAnywhere)
	float DistanceToAngleMultiplier = 0.01f;

	/**
	 * \brief Component which is used to spawn projectiles (provides transform value to projectiles)
	 */
	UPROPERTY(Category = Projectile, EditAnywhere)
	USceneComponent* GunTip;

	/**
	 * \brief Is weapon building selected by player?
	 */
	bool bIsSelected = false;

	/**
	 * \brief Did building fired on this turn already?
	 */
	bool bFiredOnThisTurn = false;

	/**
	 * \brief Respond to player clicked on this building
	 * \param Actor Self
	 * \param Key Button that was clicked
	 */
	UFUNCTION()
	void ReceiveOnBuildingClicked(AActor* Actor, FKey Key);

	/**
	 * \brief Makes building to turn towards given location (to look at it)
	 * \param Location Location to look at
	 */
	void PlanarLookAt(FVector Location);

	/**
	 * \brief Get fire manager of this building for binding to its delegates
	 * \return Fire manager of this building
	 */
	TScriptInterface<IFireManager> GetFireManager() const;
};
