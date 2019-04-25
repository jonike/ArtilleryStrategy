// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultEnemyPawn.h"

// Sets default values
ADefaultEnemyPawn::ADefaultEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADefaultEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADefaultEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
