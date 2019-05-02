// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Components/WorldGenerator.h"
#include "Components/TurnProcessorComponent.h"
#include "Engine/World.h"

ADefaultGS::ADefaultGS()
{
	WorldGenerator = CreateDefaultSubobject<UWorldGenerator>(TEXT("Grid Generator"));
	TurnProcessorComponent = CreateDefaultSubobject<UTurnProcessorComponent>(TEXT("Turn processor component"));
}

UTurnProcessorComponent* ADefaultGS::GetTurnProcessor() const
{
	return TurnProcessorComponent;
}

AInstancedMeshSpawner* ADefaultGS::GetTileMeshSpawner() const
{
	return TileMeshSpawner;
}

UWorldGenerator* ADefaultGS::GetWorldGenerator() const
{
	return WorldGenerator;
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	TileMeshSpawner = GetWorld()->SpawnActor<AInstancedMeshSpawner>(InstancedMeshSpawnerClass);
}

void ADefaultGS::BeginPlay()
{
	Super::BeginPlay();
}
