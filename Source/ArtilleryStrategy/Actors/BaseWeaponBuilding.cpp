// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponBuilding.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

ABaseWeaponBuilding::ABaseWeaponBuilding()
{
	GunTip = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Tip"));
	GunTip->SetupAttachment(RootComponent);
}

void ABaseWeaponBuilding::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseWeaponBuilding::WhenBuildingClicked);
}

void ABaseWeaponBuilding::Tick(float DeltaSeconds)
{
	if (bIsSelected)
	{
		FHitResult Hit;
		if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Camera, true, Hit))
		{
			PlanarLookAt(Hit.Location);
		}
	}
}

void ABaseWeaponBuilding::WhenBuildingClicked(AActor*, FKey)
{
	bIsSelected = !bIsSelected;
}

void ABaseWeaponBuilding::PlanarLookAt(const FVector Location)
{
	const auto Direction = Location - GetActorLocation();
	const auto Rotation = Direction.Rotation();
	SetPlaneAngle(Rotation.Yaw);
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
