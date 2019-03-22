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
	InputComponent->BindAxis("MoveForward", this, &ADefaultPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADefaultPlayerController::MoveRight);
	InputComponent->BindAxis("ZoomIn", this, &ADefaultPlayerController::Zoom);
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


UMaterialInterface& ADefaultPlayerController::GetOwnerMaterial() const
{
	check(PlayerMaterial);
	return *PlayerMaterial;
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


void ADefaultPlayerController::HideBuyWidget()
{
	GetDefaultHUD().HideBuyWidget();
}

bool ADefaultPlayerController::IsBuyWidgetVisible() const
{
	return GetDefaultHUD().IsBuyWidgetsVisible();
}

void ADefaultPlayerController::BuyBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> Buildings)
{
	// TODO: provide definition
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
		HUD.ShowBuildingSelectorWidget();
	}
	else
	{
		HUD.ShowBuyCellWidget(PropertyToBuy);
	}
}
