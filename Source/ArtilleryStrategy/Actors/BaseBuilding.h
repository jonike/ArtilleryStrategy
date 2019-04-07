// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Building.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/TurnDependent.h"
#include "BaseBuilding.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseBuilding : public AActor, public IBuilding, public ICanBeOwned, public ITurnDependent
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseBuilding();

	UFUNCTION()
	void ReceiveOnTurnEnded() override;

	TScriptInterface<IOwnerController> GetOwnerController() const override { return OwnerController; }
	void SetOwnerController(TScriptInterface<IOwnerController> NewOwner) override;
	bool HasOwnerController() const override { return OwnerController.GetObject() != nullptr; }

	// Inherited via IBuilding
	void PostPlaced(TScriptInterface<IGridPlatform> Tile) override;
	void PrePlaced(TScriptInterface<IGridPlatform> Tile) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(Category = Visuals, EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(Category = Health, EditAnywhere)
	float Health = 200.f;

	TScriptInterface<IOwnerController> OwnerController;
};
