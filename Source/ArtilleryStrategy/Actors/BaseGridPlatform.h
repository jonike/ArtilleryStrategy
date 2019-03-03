// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/GridPlatform.h"
#include "Interfaces/CanBeOwned.h"
#include "Interfaces/OwnerController.h"
#include "BaseGridPlatform.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseGridPlatform : public AActor, public IGridPlatform, public ICanBeOwned
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGridPlatform();

	// Called every frame
	void Tick(float DeltaTime) override;

	IOwnerController* GetOwnerController() const override;
	void SetOwnerController(IOwnerController& NewOwner) override;
	bool HasOwnerController() const override;
	int GetCost() const override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	void NotifyActorOnClicked(FKey ButtonPressed) override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = Cost)
		int Cost = 50;

	UFUNCTION()
		void AfterClicked(AActor* TouchedActor, FKey ButtonPressed);

	TScriptInterface<IOwnerController> OwnerController;
};
