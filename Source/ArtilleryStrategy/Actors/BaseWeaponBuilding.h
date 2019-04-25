// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/WeaponBuilding.h"
#include "BaseWeaponBuilding.generated.h"

class IFireManager;

/**
 * 
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
	void PostInitializeComponents() override;

	void ReceiveOnTurnStarted() override;
	void ReceiveOnTurnEnded() override;

private:
	UPROPERTY(Category = Projectile, EditAnywhere, meta = (MustImplement = "Projectile"))
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(Category = Projectile, EditAnywhere)
	float ProjectileImpulse = 200.F;

	UPROPERTY(Category = Shooting, EditAnywhere)
	float MinShootAngle = 0.f;

	UPROPERTY(Category = Shooting, EditAnywhere)
	float MaxShootAngle = 60.f;

	UPROPERTY(Category = Shooting, EditAnywhere)
	float DistanceToAngleMultiplier = 0.01f;

	UPROPERTY(Category = Projectile, EditAnywhere)
	USceneComponent* GunTip;

	bool bIsSelected = false;
	bool bFiredOnThisTurn = false;

	UFUNCTION()
	void ReceiveOnBuildingClicked(AActor* Actor, FKey Key);

	void PlanarLookAt(FVector Location);

	TScriptInterface<IFireManager> GetFireManager() const;
};
