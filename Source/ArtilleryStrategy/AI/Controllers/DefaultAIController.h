// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyTiles.h"
#include "Interfaces/CanBuyBuildings.h"
#include "DefaultAIController.generated.h"

/**
 * \brief Base class for all AI controllers
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultAIController : public AAIController, public IOwnerController, public ICanBuyTiles, public ICanBuyBuildings
{
	GENERATED_BODY()

public:
	ADefaultAIController();

	UMaterialInterface* GetOwnerMaterial() const override;
	UTexture2D* GetOwnerIcon() const override;
	TScriptInterface<IPlayerRepository> GetWallet() const override;

	void BuyTile(TScriptInterface<IPlayerProperty> Cell) override;
	void CreateSelectedBuilding(TScriptInterface<IWorldTile> Cell, TSubclassOf<AActor> BuildingClass) override;

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
	bool TryToBuyDefaultBuilding(TSubclassOf<AActor> BuildingClass) const;
};
