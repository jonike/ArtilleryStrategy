// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/HasSpringArm.h"
#include "Widgets/BuyPlatformWidget.h"
#include "Interfaces/Wallet.h"
#include "Player/States/DefaultPlayerState.h" // It's not an unused header; without this line cast to IWallet doesn't compile

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
		if (auto * Pawn = GetPawnOrSpectator())
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

void ADefaultPlayerController::WhenCloseClicked()
{
	HideBuyWidget();
}

void ADefaultPlayerController::WhenBuyClicked(TScriptInterface<ICanBeOwned> PropertyToBuy)
{
	const auto Property = PropertyToBuy.GetObject();
	check(Property);
	BuyCell(*Cast<ICanBeOwned>(Property));
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

void ADefaultPlayerController::CreateBuyWidget()
{
	BuyWidget = CreateWidget<UBuyPlatformWidget>(this, BuyWidgetClass);
	check(BuyWidget);
	BuyWidget->OnBuyClicked.AddDynamic(this, &ADefaultPlayerController::WhenBuyClicked);
	BuyWidget->OnCloseClicked.AddDynamic(this, &ADefaultPlayerController::WhenCloseClicked);
}

void ADefaultPlayerController::HideBuyWidget()
{
	if (BuyWidget && IsBuyWidgetVisible())
	{
		BuyWidget->RemoveFromViewport();
	}
}

bool ADefaultPlayerController::IsBuyWidgetVisible() const
{
	return BuyWidget != nullptr && BuyWidget->IsInViewport();
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
	if (AutoCloseBuyWidget)
	{
		HideBuyWidget();
	}
}

void ADefaultPlayerController::ShowBuyWidget(ICanBeOwned& PropertyToBuy)
{
	if (PropertyToBuy.GetOwnerController() != this)
	{
		if (!BuyWidget)
		{
			CreateBuyWidget();
		}
		BuyWidget->SetPropertyToBuy(PropertyToBuy);
		if (!IsBuyWidgetVisible())
		{
			BuyWidget->AddToViewport();
		}
	}
}
