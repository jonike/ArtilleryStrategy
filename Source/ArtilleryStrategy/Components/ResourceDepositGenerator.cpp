// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceDepositGenerator.h"
#include "Interfaces/SpawnStrategy.h"
#include "Game/States/DefaultGS.h"

// Sets default values for this component's properties
UResourceDepositGenerator::UResourceDepositGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UResourceDepositGenerator::ReceiveOnGridGenerationEnded(UTileMatrix* Tiles)
{
	SpawnStrategy->SetTileMatrix(Tiles);
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

void UResourceDepositGenerator::InitializeComponent()
{
	Super::InitializeComponent();
	if (SpawnStrategyClass)
	{
		SpawnStrategy = NewObject<UObject>(this, SpawnStrategyClass);
	}
	if (const auto DefaultGS = Cast<ADefaultGS>(GetOwner()))
	{
		DefaultGS->OnGridGenerationEnded.AddDynamic(this, &UResourceDepositGenerator::ReceiveOnGridGenerationEnded);
	}
}

void UResourceDepositGenerator::CreateDeposits()
{
}

TScriptInterface<IGridPlatform> UResourceDepositGenerator::GetTileForDeposit() const
{
	return nullptr;
}
