// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeaponBuilding.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Projectile.h"
#include "Interfaces/FireManager.h"

ABaseWeaponBuilding::ABaseWeaponBuilding()
{
	GunTip = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Tip"));
	GunTip->SetupAttachment(RootComponent);
}

void ABaseWeaponBuilding::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseWeaponBuilding::WhenBuildingClicked);
	GetFireManager()->AddToFireList(this);
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

TScriptInterface<IFireManager> ABaseWeaponBuilding::GetFireManager() const
{
	return GetWorld()->GetFirstPlayerController();
}

void ABaseWeaponBuilding::Fire()
{
	if (bIsSelected)
	{
		const auto Spawned = GetWorld()->SpawnActor<AActor>(ProjectileClass, GunTip->GetComponentTransform());
		if (auto Projectile = Cast<IProjectile>(Spawned))
		{
			Projectile->SetInitialSpeed(ProjectileInitialSpeed);
		}
	}
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
