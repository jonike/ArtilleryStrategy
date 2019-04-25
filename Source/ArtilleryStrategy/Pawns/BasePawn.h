// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GenericTeamAgentInterface.h"
#include "BasePawn.generated.h"

UCLASS(Abstract)
class ARTILLERYSTRATEGY_API ABasePawn : public APawn, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	FGenericTeamId GetGenericTeamId() const override;
	void SetGenericTeamId(const FGenericTeamId& TeamID) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(Category="Teams", EditAnywhere)
	FGenericTeamId PawnTeamID;
};
