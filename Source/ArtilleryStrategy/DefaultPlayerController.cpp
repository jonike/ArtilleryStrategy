// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerController.h"
#include <Camera/CameraComponent.h>

ADefaultPlayerController::ADefaultPlayerController()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);
}

void ADefaultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADefaultPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADefaultPlayerController::MoveRight);
}

void ADefaultPlayerController::MoveForward(float Value)
{
	if (Value)
	{
		UE_LOG(LogTemp, Log, TEXT("MoveForward() was called"));
	}
}

void ADefaultPlayerController::MoveRight(float Value)
{
	if (Value)
	{
		UE_LOG(LogTemp, Log, TEXT("MoveRight() was called"));
	}
}
