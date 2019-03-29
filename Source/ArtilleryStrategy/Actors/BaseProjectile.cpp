// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Objects/KineticDamage.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
}

void ABaseProjectile::SetInitialSpeed(const float Value)
{
	Speed = Value;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::DealDamage);
}

// Called every frame
void ABaseProjectile::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(GetActorForwardVector() * DeltaTime * Speed);
}

void ABaseProjectile::DealDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FDamageEvent Event;
	Event.DamageTypeClass = UKineticDamage::StaticClass();
	OtherActor->TakeDamage(Damage, Event, GetWorld()->GetFirstPlayerController(), this);
}
