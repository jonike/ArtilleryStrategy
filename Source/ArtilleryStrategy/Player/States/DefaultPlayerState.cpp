// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"
#include "Objects/ResourceStorage.h"
#include "Objects/ResourceBuildingsManager.h"
#include "Components/TurnProcessorComponent.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	Storage = CreateDefaultSubobject<UResourceStorage>(TEXT("Resource storage"));
	ResourceBuildingsManager = CreateDefaultSubobject<UResourceBuildingsManager>(TEXT("Resource buildings manager"));
}

void ADefaultPlayerState::ReceiveOnTurnStarted()
{
	TurnLimits.ResetAllLimits();
}

void ADefaultPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ADefaultPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	const auto TurnProcessor = GetTurnProcessor(this);
	TurnProcessor->OnTurnStarted.AddDynamic(this, &ADefaultPlayerState::ReceiveOnTurnStarted);
	TurnProcessor->OnTurnEnded.AddDynamic(this, &ADefaultPlayerState::ReceiveOnTurnEnded);
}
