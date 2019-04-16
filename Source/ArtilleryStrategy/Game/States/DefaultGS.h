// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefaultGS.generated.h"

class UTurnProcessorComponent;
class IMapGenerator;
class UDEPRECATED_ResourceDepositGenerator;
class ISpawnStrategy;
class UDEPRECATED_CapitalPlacementGenerator;
class UGridGenerator;
class UTileMatrix;
class IGridPlatform;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultGS : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADefaultGS();

	UTurnProcessorComponent* GetTurnProcessor() const;

protected:
	void PostInitializeComponents() override;

private:
	UPROPERTY(Category = "Generation", EditAnywhere)
	UGridGenerator* GridGenerator;

	UPROPERTY(Category = "Turns", EditAnywhere)
	UTurnProcessorComponent* TurnProcessorComponent;
};
