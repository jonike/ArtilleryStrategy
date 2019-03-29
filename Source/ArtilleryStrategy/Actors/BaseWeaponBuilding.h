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

private:
	UPROPERTY(Category = Projectile, EditAnywhere, meta = (MustImplement = "Projectile"))
	TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(Category = Projectile, EditAnywhere)
	float ProjectileInitialSpeed = 200.F;
	UPROPERTY(Category = Projectile, EditAnywhere)
	USceneComponent* GunTip;

	bool bIsSelected = false;

	UFUNCTION()
	void WhenBuildingClicked(AActor* Actor, FKey Key);

	void PlanarLookAt(FVector Location);

	TScriptInterface<IFireManager> GetFireManager() const;
};