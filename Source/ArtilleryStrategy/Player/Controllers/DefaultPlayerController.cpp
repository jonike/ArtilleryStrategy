// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/HasSpringArm.h"
#include "Interfaces/Wallet.h"
#include "Player/HUD/DefaultHUD.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/WeaponBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Actors/BaseWeaponBuilding.h"
#include "Objects/ResourceStorage.h"
#include "Interfaces/PlayerProperty.h"

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
		if (const auto SpringArm = GetSpringArmComponent())
		{
			const auto DesiredLength = SpringArm->TargetArmLength + Value * ZoomRate;
			SpringArm->TargetArmLength = FMath::Clamp(DesiredLength, MinZoomDistance, MaxZoomDistance);
		}
	}
}

void ADefaultPlayerController::FireAllWeapon()
{
	OnFire.Broadcast();
}

bool ADefaultPlayerController::TryToBuyWithPack(const FResourcePack& ResourcePack) const
{
	const auto Wallet = GetWallet();
	if (Wallet)
	{
		const auto ResourceWallet = Wallet->GetResourceWallet();
		check(ResourceWallet);
		if (ResourceWallet->IsEnoughPack(ResourcePack))
		{
			ResourceWallet->SpendResourcePack(ResourcePack);
			return true;
		}
	}
	return false;
}

bool ADefaultPlayerController::TryToBuyDefaultBuilding(const TSubclassOf<AActor> BuildingClass) const
{
	const auto DefaultBuildingObject = Cast<IPlayerProperty>(BuildingClass.GetDefaultObject());
	check(DefaultBuildingObject);
	return TryToBuyWithPack(DefaultBuildingObject->GetResourcesToOwn());
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
	// Cast is needed because we can't add binding to interface method. We have to cast to usual class and then add binding
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

UTexture2D* ADefaultPlayerController::GetOwnerIcon() const
{
	return PlayerIcon;
}

void ADefaultPlayerController::CreateSelectedBuilding(TScriptInterface<IWorldTile> Cell, const TSubclassOf<AActor> BuildingClass)
{
	const auto State = GetPlayerState<ADefaultPlayerState>();
	check(State);
	if (State->GetTurnLimits().GetBuildingsLimit().IsLimitReached())
	{
		return;
	}

	if (TryToBuyDefaultBuilding(BuildingClass))
	{
		const auto Building = Cell->CreateBuilding(BuildingClass);
		OnBuildingCreated.Broadcast(Building);
		State->RegisterBuyingBuilding(Building);
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

void ADefaultPlayerController::BuyTile(TScriptInterface<IPlayerProperty> Cell)
{
	const auto State = GetPlayerState<ADefaultPlayerState>();
	check(State);
	if (State->GetTurnLimits().GetTilesLimit().IsLimitReached())
	{
		return;
	}

	if (TryToBuyWithPack(Cell->GetResourcesToOwn()))
	{
		Cell->SetOwnerController(this);
		OnTileBought.Broadcast(Cell.GetObject());
		State->RegisterBuyingCell(Cell.GetObject());
	}
}

void ADefaultPlayerController::ShowBuyWidget(const TScriptInterface<IPlayerProperty> PropertyToBuy)
{
	auto& HUD = GetDefaultHUD();
	if (PropertyToBuy->GetOwnerController() == this)
	{
		if (const auto GridPlatform = Cast<IWorldTile>(PropertyToBuy.GetObject()))
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
