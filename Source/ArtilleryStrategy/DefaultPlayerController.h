// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController();

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		class UCameraComponent* CameraComponent;

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);
};
