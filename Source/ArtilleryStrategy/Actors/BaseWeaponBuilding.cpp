// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseWeaponBuilding.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Projectile.h"
#include "Interfaces/FireManager.h"
#include "Components/TurnProcessorComponent.h"

ABaseWeaponBuilding::ABaseWeaponBuilding()
{
	GunTip = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Tip"));
	GunTip->SetupAttachment(RootComponent);
}

void ABaseWeaponBuilding::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseWeaponBuilding::ReceiveOnBuildingClicked);
	GetFireManager()->AddToFireList(this);
}

void ABaseWeaponBuilding::Tick(float DeltaSeconds)
{
	if (bIsSelected && IsReadyForFire())
	{
		FHitResult Hit;
		if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Camera, true, Hit))
		{
			auto Rotation = GunTip->GetComponentRotation();
			const auto DistanceVector = Hit.Location - GetActorLocation();
			Rotation.Pitch = FMath::Clamp(DistanceVector.Size() * DistanceToAngleMultiplier, MinShootAngle, MaxShootAngle);
			GunTip->SetWorldRotation(Rotation);
			PlanarLookAt(Hit.Location);
		}
	}
}

void ABaseWeaponBuilding::PostPlaced(TScriptInterface<IWorldTile> Tile)
{
	Super::PostPlaced(Tile);
	const auto TurnProcessor = GetTurnProcessor(this);
	TurnProcessor->OnTurnStarted.AddDynamic(this, &ABaseWeaponBuilding::ReceiveOnTurnStarted);
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ABaseWeaponBuilding::ReceiveOnTurnEnded);
}

void ABaseWeaponBuilding::ReceiveOnBuildingClicked(AActor*, FKey)
{
	if (IsReadyForFire())
	{
		bIsSelected = !bIsSelected;
	}
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
	if (bIsSelected && IsReadyForFire())
	{
		bFiredOnThisTurn = true;
		bIsSelected = false;
		const auto Spawned = GetWorld()->SpawnActor<AActor>(ProjectileClass, GunTip->GetComponentTransform());
#if WITH_EDITOR
		Spawned->SetFolderPath(TEXT("Projectiles"));
#endif
		if (auto Projectile = Cast<IProjectile>(Spawned))
		{
			Projectile->AddImpulse(ProjectileImpulse);
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

void ABaseWeaponBuilding::ReceiveOnTurnStarted()
{
	bFiredOnThisTurn = false;
}

void ABaseWeaponBuilding::ReceiveOnTurnEnded()
{
	bIsSelected = false;
}

bool ABaseWeaponBuilding::IsReadyForFire() const
{
	return !bFiredOnThisTurn;
}
