// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponBuilding.h"
#include "Engine/World.h"

ABaseWeaponBuilding::ABaseWeaponBuilding()
{
	GunTip = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Tip"));
	GunTip->SetupAttachment(RootComponent);
}

void ABaseWeaponBuilding::Fire()
{
	auto Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, GunTip->GetComponentTransform());
	// TODO: add force to the projectile
}

void ABaseWeaponBuilding::SetPlaneAngle(const float Angle)
{
	auto Rotation = GetActorRotation();
	Rotation.Yaw = Angle;
	SetActorRelativeRotation(Rotation);
}

void ABaseWeaponBuilding::SetHorizonAngle(const float Angle)
{
	auto Rotation = GetActorRotation();
	Rotation.Pitch = Angle;
	SetActorRelativeRotation(Rotation);
}

bool ABaseWeaponBuilding::IsReadyForFire() const
{
	// TODO: add actual implementation for IsReadyForFire()
	return true;
}
