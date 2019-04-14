// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceDepositGenerator.h"
#include "Interfaces/SpawnStrategy.h"
#include "Game/States/DefaultGS.h"
#include "Interfaces/GridPlatform.h"

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

FResourceHandle UResourceDepositGenerator::GetRandomResource() const
{
	const auto Index = FMath::RandRange(0, AvailableDeposits.Num() - 1);
	return AvailableDeposits[Index];
}

int32 UResourceDepositGenerator::GetRandomResourceAmount(const FResource& Resource) const
{
	return FMath::RandRange(Resource.MinAmountSpawned, Resource.MaxAmountSpawned);
}

void UResourceDepositGenerator::CreateDeposits()
{
	for (size_t i = 0; i < DepositsAmount; i++)
	{
		FResourceDeposit ResourceDeposit;
		ResourceDeposit.ResourceAmount.ResourceHandle = GetRandomResource();
		ResourceDeposit.ResourceAmount.Amount = GetRandomResourceAmount(ResourceDeposit.ResourceAmount.GetResource(TEXT("Getting resource data for spawning deposits")));
		GetTileForDeposit()->SetResourceDeposits(ResourceDeposit);
	}
}

TScriptInterface<IGridPlatform> UResourceDepositGenerator::GetTileForDeposit() const
{
	return SpawnStrategy->GetNextSpawnPoint();
}
