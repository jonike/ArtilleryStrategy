// Fill out your copyright notice in the Description page of Project Settings.

#include "WorldParams.h"
#include "UObjectGlobals.h"
#include "Objects/TileMatrix.h"

void FWorldParams::Initialize(UObject* Context)
{
	TileMatrix = NewObject<UTileMatrix>(Context);
	CurrentWorld = Context->GetWorld();
}
