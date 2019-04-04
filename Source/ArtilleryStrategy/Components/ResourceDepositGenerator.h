// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/ResourceDeposit.h"
#include "ResourceDepositGenerator.generated.h"


class IGridPlatform;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARTILLERYSTRATEGY_API UResourceDepositGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceDepositGenerator();

	UFUNCTION()
	void ReceiveOnGridGenerationEnd(int Rows, int Columns);

protected:
	// Called when the game starts
	void BeginPlay() override;

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	int DepositsAmount = 4;

	UPROPERTY(Category = "Resources", EditDefaultsOnly)
	TSet<UResourceDeposit*> AvailableDeposits;

	void CreateDeposits();

	TScriptInterface<IGridPlatform> GetTileForDeposit() const;
};
