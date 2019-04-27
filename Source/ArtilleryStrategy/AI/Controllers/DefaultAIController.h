// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Interfaces/CanBuyBuildings.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultAIController : public AAIController, public IOwnerController, public ICanBuyCells, public ICanBuyBuildings
{
	GENERATED_BODY()

public:
	ADefaultAIController();

	UMaterialInterface* GetOwnerMaterial() const override;
	UTexture2D* GetOwnerIcon() const override;
	TScriptInterface<IWallet> GetWallet() const override;

	void BuyCell(TScriptInterface<ICanBeOwned> Cell) override;
	void CreateSelectedBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) override;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Behavior", EditAnywhere)
	UBehaviorTree* TurnBehavior;

	UPROPERTY(Category = "Behavior", EditAnywhere)
	UBlackboardData* BlackboardData;

	UPROPERTY(Category = "Ownership", EditAnywhere)
	UMaterialInterface* OwnerMaterial;

	UPROPERTY(Category = "Ownership", EditAnywhere)
	UTexture2D* OwnerIcon;

	bool TryToBuyWithPack(const FResourcePack& ResourcePack) const;
	bool TryToBuyDefaultBuilding(const TSubclassOf<AActor> BuildingClass) const;
};
