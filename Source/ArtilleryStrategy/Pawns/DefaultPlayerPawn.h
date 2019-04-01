// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/HasSpringArm.h"
#include "DefaultPlayerPawn.generated.h"

class UInputComponent;

UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerPawn : public APawn, public IHasSpringArm
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADefaultPlayerPawn();

	// Called every frame
	void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	class USpringArmComponent* GetSpringArmComponent() const override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Components)
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, Category = Components)
		class UCameraComponent* CameraComponent;
};
