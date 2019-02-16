// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridPlatform.h"
#include "BaseGridPlatform.generated.h"

UCLASS()
class ARTILLERYSTRATEGY_API ABaseGridPlatform : public AActor, public IGridPlatform
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGridPlatform();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
		UStaticMeshComponent* StaticMesh;

	UFUNCTION()
		void AfterClicked(AActor* TouchedActor, FKey ButtonPressed);

	void NotifyActorOnClicked(FKey ButtonPressed) override;
};
