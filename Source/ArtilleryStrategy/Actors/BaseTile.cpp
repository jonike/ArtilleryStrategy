// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTile.h"
#include "ArtilleryStrategy.h"
#include "Engine/World.h"
#include "Interfaces/OwnerController.h"
#include "Components/BoxComponent.h"
#include "Components/BillboardComponent.h"
#include "Structs/ResourceDeposit.h"
#include "Interfaces/Building.h"
#include "GameFramework/PlayerController.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Game/States/DefaultGS.h"
#include "InstancedMeshSpawner.h"
#include "Interfaces/NeedsBuyWidget.h"
#include "Structs/TileData.h"

// Sets default values
ABaseTile::ABaseTile()
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

void ABaseTile::SetTileData(const FTileData Data)
{
	TileData = Data;
}

const FTileData& ABaseTile::GetTileData()
{
	return TileData;
}

// Called when the game starts or when spawned
void ABaseTile::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseTile::ReceiveOnClicked);
	AddInstancedMesh();
}

void ABaseTile::ReceiveOnClicked(AActor*, FKey)
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (auto ControllerThatCanBuy = Cast<INeedsBuyWidget>(PlayerController))
	{
		ControllerThatCanBuy->ShowBuyWidget(this);
	}
}

void ABaseTile::AddInstancedMesh()
{
	const auto InstancedMeshSpawner = GetInstancedMeshSpawner();
	check(InstancedMeshSpawner);
	const FTransform InstanceTransform(FQuat::Identity, GetActorLocation() + InstancedMeshOffset, FVector::OneVector);
	MeshInstanceIndex = InstancedMeshSpawner->GetTileInstancedMesh()->AddInstance(InstanceTransform);
}

AInstancedMeshSpawner* ABaseTile::GetInstancedMeshSpawner() const
{
	const auto GameState = GetWorld()->GetGameState<ADefaultGS>();
	check(GameState);
	return GameState->GetTileMeshSpawner();
}

void ABaseTile::NotifyActorOnClicked(FKey)
{
	UE_LOG(MouseInteraction, Verbose, TEXT("Platform clicked"));
}

FVector ABaseTile::GetBuildingSpawnLocation() const
{
	return GetActorLocation() + BuildingSpawnOffset;
}

bool ABaseTile::HasBuilding() const
{
	return Building.GetObject() != nullptr;
}

AActor* ABaseTile::SpawnBuildingActor(const TSubclassOf<AActor> BuildingClass) const
{
	const auto Location = GetBuildingSpawnLocation();
	const auto Spawned = GetWorld()->SpawnActor(BuildingClass, &Location);
	check(Spawned);
#if WITH_EDITOR
	Spawned->SetFolderPath("World/Buildings");
#endif
	return Spawned;
}

void ABaseTile::SetBuilding(const TScriptInterface<IBuilding> SpawnedBuilding)
{
	check(SpawnedBuilding);
	SpawnedBuilding->PrePlaced(this);
	Building = SpawnedBuilding;
	SpawnedBuilding->PostPlaced(this);
}

TScriptInterface<IBuilding> ABaseTile::SpawnBuilding(TSubclassOf<AActor> BuildingClass)
{
	const auto SpawnedBuilding = SpawnBuildingActor(BuildingClass);
	SetBuilding(SpawnedBuilding);
	if (const auto OwnedBuilding = Cast<IPlayerProperty>(SpawnedBuilding))
	{
		OwnedBuilding->SetOwnerController(GetOwnerController());
	}
	return SpawnedBuilding;
}

TSet<FResourceDeposit>& ABaseTile::GetResourceDeposits()
{
	return ResourceDeposits;
}

bool ABaseTile::HasResourceDeposits() const
{
	return ResourceDeposits.Num() > 0;
}

void ABaseTile::SetResourceDeposits(FResourceDeposit& Deposit)
{
	ResourceDeposits.Add(Deposit);
	ResourceBillboard->SetSprite(Deposit.ResourceAmount.GetResource(TEXT("Setting sprite for resource deposit on the tile")).Icon);
	ResourceBillboard->bHiddenInGame = false;
}

TScriptInterface<IOwnerController> ABaseTile::GetOwnerController() const
{
	return OwnerController;
}

void ABaseTile::SetOwnerController(TScriptInterface<IOwnerController> NewOwner)
{
	OwnerController = NewOwner;
	OwnerIconBillboard->SetSprite(NewOwner->GetOwnerIcon());
	OwnerIconBillboard->bHiddenInGame = false;
}

bool ABaseTile::HasOwnerController() const
{
	return OwnerController != nullptr;
}

bool ABaseTile::RequiresResourcesToOwn() const
{
	return ResourcesToOwn.Resources.Num() != 0;
}

const FResourcePack& ABaseTile::GetResourcesToOwn() const
{
	return ResourcesToOwn;
}

// Called every frame
void ABaseTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
