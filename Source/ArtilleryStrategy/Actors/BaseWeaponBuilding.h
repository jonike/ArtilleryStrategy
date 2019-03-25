// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseBuilding.h"
#include "Interfaces/WeaponBuilding.h"
#include "BaseWeaponBuilding.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseWeaponBuilding : public ABaseBuilding, public IWeaponBuilding
{
	GENERATED_BODY()

public:
	ABaseWeaponBuilding();

	void Fire() override;

	void SetPlaneAngle(float Angle) override;

	void SetHorizonAngle(float Angle) override;

	bool IsReadyForFire() const override;

private:
	UPROPERTY(Category = Projectile, EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(Category = Projectile, EditAnywhere)
	float FireForce = 200.F;

	UPROPERTY(Category = Projectile, EditAnywhere)
	USceneComponent* GunTip;
};
