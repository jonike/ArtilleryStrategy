// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBuilding.h"
#include "Components/StaticMeshComponent.h"
#include "Interfaces/OwnerController.h"
#include "ArtilleryStrategy.h"

// Sets default values
ABaseBuilding::ABaseBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();
}

float ABaseBuilding::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!IsPendingKillPending())
	{
		Health -= DamageAmount;
		if (Health <= 0.f)
		{
			Destroy();
		}
	}
	return DamageAmount;
}

FResourcePack ABaseBuilding::GetResourcesToOwn() const
{
	return ResourcesToOwn;
}

void ABaseBuilding::PostPlaced(const TScriptInterface<IGridPlatform> Tile)
{
	UnderlyingTile = Tile;
}

void ABaseBuilding::PrePlaced(TScriptInterface<IGridPlatform> Tile)
{
}

void ABaseBuilding::ReceiveOnTurnEnded()
{
	UE_LOG(TurnProcessing, Log, TEXT("Turn ended for resource building"));
}

void ABaseBuilding::SetOwnerController(TScriptInterface<IOwnerController> NewOwner)
{
	OwnerController = NewOwner;
	StaticMesh->SetMaterial(0, OwnerController->GetOwnerMaterial());
}

bool ABaseBuilding::RequiresResourcesToOwn() const
{
	return ResourcesToOwn.Resources.Num() != 0;
}

// Called every frame
void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
