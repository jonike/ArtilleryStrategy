// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"

void ADefaultPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Storage = NewObject<UResourceStorage>();
}
