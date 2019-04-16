// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGS.h"
#include "Components/WorldGenerator.h"
#include "Components/TurnProcessorComponent.h"

ADefaultGS::ADefaultGS()
{
	GridGenerator = CreateDefaultSubobject<UGridGenerator>(TEXT("Grid Generator"));
	TurnProcessorComponent = CreateDefaultSubobject<UTurnProcessorComponent>(TEXT("Turn processor component"));
}

UTurnProcessorComponent* ADefaultGS::GetTurnProcessor() const
{
	return TurnProcessorComponent;
}

void ADefaultGS::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
