// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Building.h"
#include "Interfaces/CanBeOwned.h"
#include "BaseBuilding.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseBuilding : public AActor, public IBuilding, public ICanBeOwned
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseBuilding();

	// Called every frame
	void Tick(float DeltaTime) override;

	TScriptInterface<IOwnerController> GetOwnerController() const override { return OwnerController; }
	void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) override;
	int GetCost() const override { return Cost; }
	bool HasOwnerController() const override { return OwnerController.GetObject() != nullptr; }

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

private:
	UPROPERTY(Category = Visuals, EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = Cost)
	int Cost = 50;

	TScriptInterface<IOwnerController> OwnerController;
};
