// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDepositGenerator.h"

// Sets default values for this component's properties
UResourceDepositGenerator::UResourceDepositGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UResourceDepositGenerator::ReceiveOnGridGenerationEnd(int Rows, int Columns)
{
	CreateDeposits();
}


// Called when the game starts
void UResourceDepositGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UResourceDepositGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceDepositGenerator::CreateDeposits()
{
}

TScriptInterface<IGridPlatform> UResourceDepositGenerator::GetTileForDeposit() const
{
	return nullptr;
}

