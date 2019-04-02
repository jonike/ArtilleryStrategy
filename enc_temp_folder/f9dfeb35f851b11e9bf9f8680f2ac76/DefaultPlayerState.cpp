// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"

ADefaultPlayerState::ADefaultPlayerState()
{
	Storage = CreateDefaultSubobject<UResourceStorage>(TEXT("Resource storage"));
}
