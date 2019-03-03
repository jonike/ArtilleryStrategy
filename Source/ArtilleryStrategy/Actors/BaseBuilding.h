// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Building.h"
#include "BaseBuilding.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseBuilding : public AActor, public IBuilding
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseBuilding();

	// Called every frame
	void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(Category = Visuals, EditAnywhere)
		UStaticMeshComponent* StaticMesh;
};
