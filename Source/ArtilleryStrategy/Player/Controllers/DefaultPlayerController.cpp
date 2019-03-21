// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/HasSpringArm.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Interfaces/Wallet.h"
#include "Player/States/DefaultPlayerState.h" // It's not an unused header; without this line cast to IWallet doesn't compile
#include "Widgets/BuildingSelectorWidget.h"
#include "Player/HUD/DefaultHUD.h"

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

void ADefaultPlayerController::MoveForward(float Value)
{
	if (Value)
	{
		if (auto* Pawn = GetPawnOrSpectator())
		{
			Pawn->AddActorLocalOffset(FVector::ForwardVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::MoveRight(float Value)
{
	if (Value)
	{
		if (auto Pawn = GetPawnOrSpectator())
		{
			Pawn->AddActorLocalOffset(FVector::RightVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::Zoom(float Value)
{
	if (Value)
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

IWallet& ADefaultPlayerController::GetWallet() const
{
	const auto State = GetPlayerState<APlayerState>();
	check(State);
	const auto Wallet = Cast<IWallet>(State);
	check(Wallet);
	return *Wallet;
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

USpringArmComponent* ADefaultPlayerController::GetSpringArmComponent() const
{
	if (const auto Pawn = GetPawnOrSpectator())
	{
		if (const auto PawnWithSpringArm = Cast<IHasSpringArm>(Pawn))
		{
			return PawnWithSpringArm->GetSpringArmComponent();
		}
	}
	return nullptr;
}

void ADefaultPlayerController::BuyCell(ICanBeOwned& Cell)
{
	auto& Wallet = GetWallet();
	if (Wallet.IsEnoughMoney(Cell.GetCost()))
	{
		Cell.SetOwnerController(*this);
		Wallet.RemoveMoney(Cell.GetCost());
	}
}

void ADefaultPlayerController::ShowBuyWidget(ICanBeOwned& PropertyToBuy)
{
	auto& HUD = GetDefaultHUD();
	if (PropertyToBuy.GetOwnerController() == this)
	{
		HUD.ShowBuildingSelectorWidget();
	}
	else
	{
		HUD.ShowBuyCellWidget(PropertyToBuy);
	}
}
