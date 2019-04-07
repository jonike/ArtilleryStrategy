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

void UResourceDepositGenerator::CreateDeposits()
{
	if (ResourceTable)
	{
		for (size_t i = 0; i < DepositsAmount; i++)
		{
			// TODO: extract code to multiple methods
			const auto Names = ResourceTable->GetRowNames();
			const auto Index = FMath::RandRange(0, Names.Num() - 1);
			const auto SelectedName = Names[Index];
			const auto SelectedResource = ResourceTable->FindRow<FResource>(SelectedName, TEXT("Get random resource for resource deposit placement"));
			check(SelectedResource);
			const auto Tile = GetTileForDeposit();
			const auto Amount = FMath::RandRange(SelectedResource->MinAmountSpawned, SelectedResource->MaxAmountSpawned);
			// TODO: cleanup code
			FResourceDeposit ResourceDeposit;
			ResourceDeposit.ResourceAmount.Resource = *SelectedResource;
			ResourceDeposit.ResourceAmount.Amount = Amount;
			Tile->SetResourceDeposit(ResourceDeposit);
		}
	}
}

TScriptInterface<IGridPlatform> UResourceDepositGenerator::GetTileForDeposit() const
{
	return SpawnStrategy->GetNextSpawnPoint();
}
