// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGridPlatform.h"
#include "ArtilleryStrategy.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Structs/ResourceDeposit.h"
#include "Interfaces/Building.h"

// Sets default values
ABaseGridPlatform::ABaseGridPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
	ResourceBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Resource billboard"));
	ResourceBillboard->SetupAttachment(RootComponent);
	ResourceBillboard->bHiddenInGame = true;
	ResourceBillboard->bIsScreenSizeScaled = true;
}

// Called when the game starts or when spawned
void ABaseGridPlatform::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseGridPlatform::ReceiveOnClicked);
}

void ABaseGridPlatform::ReceiveOnClicked(AActor*, FKey)
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (auto ControllerThatCanBuy = Cast<ICanBuyCells>(PlayerController))
	{
		ControllerThatCanBuy->ShowBuyWidget(this);
	}
}

void ABaseGridPlatform::NotifyActorOnClicked(FKey)
{
	UE_LOG(MouseInteraction, Verbose, TEXT("Platform clicked"));
}

int ABaseGridPlatform::GetCost() const
{
	return Cost;
}

FVector ABaseGridPlatform::GetBuildingSpawnLocation() const
{
	return GetActorLocation() + BuildingSpawnOffset;
}

bool ABaseGridPlatform::HasBuilding() const
{
	return Building.GetObject() != nullptr;
}

void ABaseGridPlatform::SetBuilding(const TScriptInterface<IBuilding> SpawnedBuilding)
{
	check(SpawnedBuilding);
	SpawnedBuilding->PrePlaced(this);
	Building = SpawnedBuilding;
	SpawnedBuilding->PostPlaced(this);
}

UResourceDeposit* ABaseGridPlatform::GetResourceDeposit() const
{
	return ResourceDeposit;
}

bool ABaseGridPlatform::HasResourceDeposit() const
{
	return ResourceDeposit != nullptr;
}

void ABaseGridPlatform::SetResourceDeposit(UResourceDeposit* Deposit)
{
	check(Deposit);
	ResourceDeposit = Deposit;
	ResourceBillboard->SetSprite(Deposit->GetResource().Icon);
	ResourceBillboard->bHiddenInGame = false;
}

TScriptInterface<IOwnerController> ABaseGridPlatform::GetOwnerController() const
{
	return OwnerController;
}

void ABaseGridPlatform::SetOwnerController(TScriptInterface<IOwnerController> NewOwner)
{
	OwnerController = NewOwner;
	StaticMesh->SetMaterial(0, NewOwner->GetOwnerMaterial());
}

bool ABaseGridPlatform::HasOwnerController() const
{
	return OwnerController != nullptr;
}

// Called every frame
void ABaseGridPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
