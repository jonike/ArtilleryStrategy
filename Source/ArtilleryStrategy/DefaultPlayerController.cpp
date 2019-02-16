// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "HasSpringArm.h"

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
		auto* Pawn = GetPawnOrSpectator();
		if (Pawn)
		{
			Pawn->AddActorLocalOffset(FVector::ForwardVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::MoveRight(float Value)
{
	if (Value)
	{
		auto Pawn = GetPawnOrSpectator();
		if (Pawn)
		{
			Pawn->AddActorLocalOffset(FVector::RightVector * Value * MaxMovementSpeed);
		}
	}
}

void ADefaultPlayerController::Zoom(float Value)
{
	if (Value)
	{
		auto SpringArm = GetSpringArmComponent();
		if (SpringArm)
		{
			SpringArm->TargetArmLength += Value * ZoomRate;
		}
	}
}

USpringArmComponent* ADefaultPlayerController::GetSpringArmComponent() const
{
	const auto Pawn = GetPawnOrSpectator();
	if (Pawn)
	{
		const auto PawnWithSpringArm = Cast<IHasSpringArm>(Pawn);
		if (PawnWithSpringArm)
		{
			return PawnWithSpringArm->GetSpringArmComponent();
		}
	}
	return nullptr;
}

void ADefaultPlayerController::BuyCell(IGridPlatform * Cell)
{
	unimplemented();
}

void ADefaultPlayerController::ShowBuyWidget()
{
	unimplemented();
}
