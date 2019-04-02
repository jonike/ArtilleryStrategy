// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArtilleryStrategyGMB.generated.h"

class UCapitalPlacementGenerator;
class UGridGenerator;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API AArtilleryStrategyGMB : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArtilleryStrategyGMB();
};
