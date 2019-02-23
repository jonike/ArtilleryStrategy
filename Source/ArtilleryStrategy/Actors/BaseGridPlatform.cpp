// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGridPlatform.h"
#include "ArtilleryStrategy.h"
#include "Engine/World.h"
#include "Interfaces/CanBuyCells.h"

// Sets default values
ABaseGridPlatform::ABaseGridPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ABaseGridPlatform::BeginPlay()
{
	Super::BeginPlay();
	OnClicked.AddDynamic(this, &ABaseGridPlatform::AfterClicked);
}

void ABaseGridPlatform::AfterClicked(AActor*, FKey)
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	check(PlayerController);
	if (auto ControllerThatCanBuy = Cast<ICanBuyCells>(PlayerController))
	{
		ControllerThatCanBuy->ShowBuyWidget();
	}
}

void ABaseGridPlatform::NotifyActorOnClicked(FKey)
{
	UE_LOG(MouseInteraction, Verbose, TEXT("Platform clicked"));
}

AController* ABaseGridPlatform::GetOwnerController() const
{
	return OwnerController;
}

void ABaseGridPlatform::SetOwnerController(AController& NewOwner)
{
	OwnerController = &NewOwner;
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
