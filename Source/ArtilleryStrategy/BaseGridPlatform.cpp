// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGridPlatform.h"

// Sets default values
ABaseGridPlatform::ABaseGridPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABaseGridPlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseGridPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
