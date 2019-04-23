// Fill out your copyright notice in the Description page of Project Settings.


#include "InstancedMeshSpawner.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

// Sets default values
AInstancedMeshSpawner::AInstancedMeshSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TileInstancedMesh = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Tile instanced mesh"));
	TileInstancedMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInstancedMeshSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstancedMeshSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

