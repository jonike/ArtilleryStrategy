// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/HasSpringArm.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Interfaces/Wallet.h"
#include "Widgets/BuildingSelectorWidget.h"
#include "Player/HUD/DefaultHUD.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/WeaponBuilding.h"
#include "Interfaces/GridPlatform.h"
#include "Actors/BaseWeaponBuilding.h"

ADefaultPlayerController::ADefaultPlayerController()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &ADefaultPlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &ADefaultPlayerController::MoveRight);
	InputComponent->BindAxis(TEXT("ZoomIn"), this, &ADefaultPlayerController::Zoom);

	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADefaultPlayerController::FireAllWeapon);
}

void ADefaultPlayerController::MoveForward(const float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		if (auto PlayerPawn = GetPawnOrSpectator())
		{
			PlayerPawn->AddActorLocalOffset(FVector::ForwardVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::MoveRight(const float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		if (auto PlayerPawn = GetPawnOrSpectator())
		{
			PlayerPawn->AddActorLocalOffset(FVector::RightVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::Zoom(const float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		if (auto SpringArm = GetSpringArmComponent())
		{
			SpringArm->TargetArmLength += Value * ZoomRate;
		}
	}
}

void ADefaultPlayerController::FireAllWeapon()
{
	OnFire.Broadcast();
}


UMaterialInterface* ADefaultPlayerController::GetOwnerMaterial() const
{
	check(PlayerMaterial);
	return PlayerMaterial;
}

TScriptInterface<IWallet> ADefaultPlayerController::GetWallet() const
{
	const auto State = GetPlayerState<APlayerState>();
	check(State);
	return State;
}

ADefaultHUD& ADefaultPlayerController::GetDefaultHUD() const
{
	const auto HUD = GetHUD();
	check(HUD);
	const auto DefaultHUD = Cast<ADefaultHUD>(HUD);
	check(DefaultHUD);
	return *DefaultHUD;
}

void ADefaultPlayerController::AddToFireList(const TScriptInterface<IWeaponBuilding> Weapon)
{
	// TODO: ugly cast (interface -> abstract class)
	const auto WeaponBuilding = Cast<ABaseWeaponBuilding>(Weapon.GetObject());
	check(WeaponBuilding);
	OnFire.AddDynamic(WeaponBuilding, &ABaseWeaponBuilding::Fire);
}


void ADefaultPlayerController::HideBuyWidget()
{
	GetDefaultHUD().HideBuyWidget();
}

bool ADefaultPlayerController::IsBuyWidgetVisible() const
{
	return GetDefaultHUD().IsBuyWidgetsVisible();
}

void ADefaultPlayerController::BuyBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass)
{
	const auto Location = Cell->GetBuildingSpawnLocation();
	const auto SpawnedBuilding = GetWorld()->SpawnActor(BuildingClass, &Location);
	Cell->SetBuilding(SpawnedBuilding);
	if (const auto OwnedBuilding = Cast<ICanBeOwned>(SpawnedBuilding))
	{
		OwnedBuilding->SetOwnerController(this);
	}
}

USpringArmComponent* ADefaultPlayerController::GetSpringArmComponent() const
{
	if (const auto PlayerPawn = GetPawnOrSpectator())
	{
		if (const auto PawnWithSpringArm = Cast<IHasSpringArm>(PlayerPawn))
		{
			return PawnWithSpringArm->GetSpringArmComponent();
		}
	}
	return nullptr;
}

void ADefaultPlayerController::BuyCell(TScriptInterface<ICanBeOwned> Cell)
{
	auto Wallet = GetWallet();
	if (Wallet->IsEnoughMoney(Cell->GetCost()))
	{
		Cell->SetOwnerController(this);
		Wallet->RemoveMoney(Cell->GetCost());
	}
}

void ADefaultPlayerController::ShowBuyWidget(TScriptInterface<ICanBeOwned> PropertyToBuy)
{
	auto& HUD = GetDefaultHUD();
	if (PropertyToBuy->GetOwnerController() == this)
	{
		if (const auto GridPlatform = Cast<IGridPlatform>(PropertyToBuy.GetObject()))
		{
			if (!GridPlatform->HasBuilding())
			{
				HUD.ShowBuildingSelectorWidget(PropertyToBuy.GetObject());
			}
		}
	}
	else
	{
		HUD.ShowBuyCellWidget(PropertyToBuy);
	}
}
