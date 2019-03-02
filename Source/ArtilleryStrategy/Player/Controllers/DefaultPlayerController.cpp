// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/HasSpringArm.h"
#include "Widgets/BuyPlatformWidget.h"

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

FColor ADefaultPlayerController::GetOwnerColor() const
{
	return PlayerColor;
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
	// unimplemented();
}

void ADefaultPlayerController::ShowBuyWidget(ICanBeOwned& PropertyToBuy)
{
	if (!BuyWidget)
	{
		BuyWidget = CreateWidget<UBuyPlatformWidget>(this, BuyWidgetClass);
		check(BuyWidget);
		BuyWidget->OnBuyClicked.AddDynamic(this, &ADefaultPlayerController::WhenBuyClicked);
		BuyWidget->OnCloseClicked.AddDynamic(this, &ADefaultPlayerController::WhenCloseClicked);
	}
	BuyWidget->SetPropertyToBuy(PropertyToBuy);
	if (!IsBuyWidgetVisible())
	{
		BuyWidget->AddToViewport();
	}
}
