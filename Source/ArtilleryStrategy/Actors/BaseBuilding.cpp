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
auto ABaseBuilding::BeginPlay() -> void
{
	Super::BeginPlay();
}

auto ABaseBuilding::TakeDamage(const float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) -> float
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

auto ABaseBuilding::GetResourcesToOwn() const -> const FResourcePack&
{
	return ResourcesToOwn;
}

auto ABaseBuilding::PostPlaced(const TScriptInterface<IWorldTile> Tile) -> void
{
	UnderlyingTile = Tile;
}

auto ABaseBuilding::PrePlaced(TScriptInterface<IWorldTile> Tile) -> void
{
}

auto ABaseBuilding::ReceiveOnTurnEnded() -> void
{
	UE_LOG(TurnProcessing, Log, TEXT("Turn ended for resource building"));
}

auto ABaseBuilding::GetOwnerController() const -> TScriptInterface<IOwnerController>
{
	return OwnerController;
}

auto ABaseBuilding::SetOwnerController(TScriptInterface<IOwnerController> NewOwner) -> void
{
	OwnerController = NewOwner;
	StaticMesh->SetMaterial(0, OwnerController->GetOwnerMaterial());
}

auto ABaseBuilding::HasOwnerController() const -> bool
{
	return OwnerController.GetObject() != nullptr;
}

auto ABaseBuilding::RequiresResourcesToOwn() const -> bool
{
	return ResourcesToOwn.Resources.Num() != 0;
}

// Called every frame
auto ABaseBuilding::Tick(float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
}
