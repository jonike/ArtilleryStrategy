// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurnProcessorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARTILLERYSTRATEGY_API UTurnProcessorComponent : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnStartedSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTurnEndedSignature);

public:
	// Sets default values for this component's properties
	UTurnProcessorComponent();

	FOnTurnStartedSignature OnTurnStarted;
	FOnTurnEndedSignature OnTurnEnded;

	void EndTurn();

protected:
	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void PrepareForNextTurn();
};
