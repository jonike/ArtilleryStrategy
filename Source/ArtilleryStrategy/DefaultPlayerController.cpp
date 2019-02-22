// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "HasSpringArm.h"
#include "UserWidget.h"

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

void ADefaultPlayerController::HideBuyWidget()
{
	if (BuyWidget)
	{
		BuyWidget->RemoveFromViewport();
	}
}

bool ADefaultPlayerController::IsBuyWidgetVisible() const
{
	return false/*BuyWidget != nullptr && BuyWidget->IsInViewport()*/;
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

void ADefaultPlayerController::BuyCell(IGridPlatform* Cell)
{
	// unimplemented();
}

void ADefaultPlayerController::ShowBuyWidget()
{
	if (!BuyWidget)
	{
		BuyWidget = CreateWidget<UUserWidget, APlayerController>(this, BuyWidgetClass->StaticClass(), TEXT("BuyWidget"));
	}
	BuyWidget->AddToViewport();
}
