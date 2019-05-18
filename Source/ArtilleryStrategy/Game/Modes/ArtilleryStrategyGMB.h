// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "ArtilleryStrategyGMB.generated.h"

/**
 * \brief Base class for all game modes
 */
UCLASS()
class ARTILLERYSTRATEGY_API AArtilleryStrategyGMB : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArtilleryStrategyGMB();

protected:
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	int AIPlayers = 3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> AIActorClass;
};
