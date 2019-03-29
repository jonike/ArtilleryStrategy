// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Projectile.h"
#include "BaseProjectile.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseProjectile : public AActor, public IProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

	void SetInitialSpeed(float Value) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:
	float Speed = 0.0F;
};