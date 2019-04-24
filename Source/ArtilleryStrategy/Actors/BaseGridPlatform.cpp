// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGridPlatform.h"
#include "ArtilleryStrategy.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Structs/ResourceDeposit.h"
#include "Interfaces/Building.h"
#include "GameFramework/PlayerController.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Game/States/DefaultGS.h"
#include "InstancedMeshSpawner.h"

// Sets default values
ABaseGridPlatform::ABaseGridPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Mesh"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	CollisionBox->SetCollisionProfileName(TEXT("BlockAll"));
	ResourceBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Resource billboard"));
	ResourceBillboard->SetupAttachment(RootComponent);
	ResourceBillboard->bHiddenInGame = true;
	ResourceBillboard->bIsScreenSizeScaled = true;
	OwnerIconBillboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Owner icon billboard"));
	OwnerIconBillboard->SetupAttachment(RootComponent);
	OwnerIconBillboard->bHiddenInGame = true;
	OwnerIconBillboard->bIsScreenSizeScaled = true;
}

// Called when the game starts or when spawned
void ABaseGridPlatform::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseGridPlatform::ReceiveOnClicked);
	AddInstancedMesh();
}

void ABaseGridPlatform::ReceiveOnClicked(AActor*, FKey)
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (auto ControllerThatCanBuy = Cast<ICanBuyCells>(PlayerController))
	{
		ControllerThatCanBuy->ShowBuyWidget(this);
	}
}

void ABaseGridPlatform::AddInstancedMesh()
{
	const auto InstancedMeshSpawner = GetInstancedMeshSpawner();
	check(InstancedMeshSpawner);
	const FTransform InstanceTransform(FQuat::Identity, GetActorLocation() + InstancedMeshOffset, FVector::OneVector);
	MeshInstanceIndex = InstancedMeshSpawner->GetTileInstancedMesh()->AddInstance(InstanceTransform);
}

AInstancedMeshSpawner* ABaseGridPlatform::GetInstancedMeshSpawner() const
{
	const auto GameState = GetWorld()->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetTileMeshSpawner();
}

void ABaseGridPlatform::NotifyActorOnClicked(FKey)
{
	UE_LOG(MouseInteraction, Verbose, TEXT("Platform clicked"));
}

FVector ABaseGridPlatform::GetBuildingSpawnLocation() const
{
	return GetActorLocation() + BuildingSpawnOffset;
}

bool ABaseGridPlatform::HasBuilding() const
{
	return Building.GetObject() != nullptr;
}

AActor* ABaseGridPlatform::SpawnBuildingActor(const TSubclassOf<AActor> BuildingClass) const
{
	const auto Location = GetBuildingSpawnLocation();
	const auto Spawned = GetWorld()->SpawnActor(BuildingClass, &Location);
	check(Spawned);
#if WITH_EDITOR
	Spawned->SetFolderPath("World/Buildings");
#endif
	return Spawned;
}

void ABaseGridPlatform::SetBuilding(const TScriptInterface<IBuilding> SpawnedBuilding)
{
	check(SpawnedBuilding);
	SpawnedBuilding->PrePlaced(this);
	Building = SpawnedBuilding;
	SpawnedBuilding->PostPlaced(this);
}

TScriptInterface<IBuilding> ABaseGridPlatform::CreateBuilding(TSubclassOf<AActor> BuildingClass)
{
	const auto SpawnedBuilding = SpawnBuildingActor(BuildingClass);
	SetBuilding(SpawnedBuilding);
	if (const auto OwnedBuilding = Cast<ICanBeOwned>(SpawnedBuilding))
	{
		OwnedBuilding->SetOwnerController(GetOwnerController());
	}
	return SpawnedBuilding;
}

TSet<FResourceDeposit>& ABaseGridPlatform::GetResourceDeposits()
{
	return ResourceDeposits;
}

bool ABaseGridPlatform::HasResourceDeposits() const
{
	return ResourceDeposits.Num() > 0;
}

void ABaseGridPlatform::SetResourceDeposits(FResourceDeposit& Deposit)
{
	ResourceDeposits.Add(Deposit);
	ResourceBillboard->SetSprite(Deposit.ResourceAmount.GetResource(TEXT("Setting sprite for resource deposit on the tile")).Icon);
	ResourceBillboard->bHiddenInGame = false;
}

TScriptInterface<IOwnerController> ABaseGridPlatform::GetOwnerController() const
{
	return OwnerController;
}

void ABaseGridPlatform::SetOwnerController(TScriptInterface<IOwnerController> NewOwner)
{
	OwnerController = NewOwner;
	OwnerIconBillboard->SetSprite(NewOwner->GetOwnerIcon());
	OwnerIconBillboard->bHiddenInGame = false;
}

bool ABaseGridPlatform::HasOwnerController() const
{
	return OwnerController != nullptr;
}

bool ABaseGridPlatform::RequiresResourcesToOwn() const
{
	return ResourcesToOwn.Resources.Num() != 0;
}

const FResourcePack& ABaseGridPlatform::GetResourcesToOwn() const
{
	return ResourcesToOwn;
}

// Called every frame
void ABaseGridPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
