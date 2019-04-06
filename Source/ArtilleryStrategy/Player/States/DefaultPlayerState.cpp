// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"
#include "Objects/ResourceStorage.h"
#include "Objects/ResourceBuildingsManager.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	Storage = CreateDefaultSubobject<UResourceStorage>(TEXT("Resource storage"));
	ResourceBuildingsManager = CreateDefaultSubobject<UResourceBuildingsManager>(TEXT("Resource buildings manager"));
}
