// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnProcessorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Objects/ResourceBuildingsManager.h"

// Sets default values for this component's properties
UTurnProcessorComponent::UTurnProcessorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTurnProcessorComponent::EndTurn()
{
	OnTurnEnded.Broadcast();
	PrepareForNextTurn();
	OnTurnStarted.Broadcast();
}

// Called when the game starts
void UTurnProcessorComponent::BeginPlay()
{
	Super::BeginPlay();
	OnTurnStarted.Broadcast();
}

// Called every frame
void UTurnProcessorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTurnProcessorComponent::PrepareForNextTurn()
{
	// logic between the turns
}
