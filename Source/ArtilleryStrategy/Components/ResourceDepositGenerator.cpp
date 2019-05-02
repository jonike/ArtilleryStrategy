// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceDepositGenerator.h"
#include "Interfaces/SpawnStrategy.h"
#include "Game/States/DefaultGS.h"
#include "Interfaces/WorldTile.h"

// Sets default values for this component's properties
UDEPRECATED_ResourceDepositGenerator::UDEPRECATED_ResourceDepositGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}

void UDEPRECATED_ResourceDepositGenerator::ReceiveOnGridGenerationEnded(UTileMatrix* Tiles)
{
	SpawnStrategy->SetTileMatrix(Tiles);
	CreateDeposits();
}

// Called when the game starts
void UDEPRECATED_ResourceDepositGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UDEPRECATED_ResourceDepositGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDEPRECATED_ResourceDepositGenerator::InitializeComponent()
{
	Super::InitializeComponent();
	if (SpawnStrategyClass)
	{
		SpawnStrategy = NewObject<UObject>(this, SpawnStrategyClass);
	}
	if (const auto DefaultGS = Cast<ADefaultGS>(GetOwner()))
	{
		// DefaultGS->OnGridGenerationEnded.AddDynamic(this, &UResourceDepositGenerator::ReceiveOnGridGenerationEnded);
	}
}

FResourceHandle UDEPRECATED_ResourceDepositGenerator::GetRandomResource() const
{
	const auto Index = FMath::RandRange(0, AvailableDeposits.Num() - 1);
	return AvailableDeposits[Index];
}

int32 UDEPRECATED_ResourceDepositGenerator::GetRandomResourceAmount(const FResource& Resource) const
{
	return FMath::RandRange(Resource.MinAmountSpawned, Resource.MaxAmountSpawned);
}

void UDEPRECATED_ResourceDepositGenerator::CreateDeposits()
{
	for (size_t i = 0; i < DepositsAmount; i++)
	{
		FResourceDeposit ResourceDeposit;
		ResourceDeposit.ResourceAmount.ResourceHandle = GetRandomResource();
		ResourceDeposit.ResourceAmount.Amount = GetRandomResourceAmount(ResourceDeposit.ResourceAmount.GetResource(TEXT("Getting resource data for spawning deposits")));
		GetTileForDeposit()->SetResourceDeposits(ResourceDeposit);
	}
}

TScriptInterface<IWorldTile> UDEPRECATED_ResourceDepositGenerator::GetTileForDeposit() const
{
	return SpawnStrategy->GetNextSpawnPoint();
}
