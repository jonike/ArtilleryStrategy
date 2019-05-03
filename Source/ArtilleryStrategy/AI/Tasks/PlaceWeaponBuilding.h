// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PlaceWeaponBuilding.generated.h"

class IWorldTile;
class UDataTable;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UPlaceWeaponBuilding : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPlaceWeaponBuilding();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	UDataTable* WeaponBuildingsTable;

	TScriptInterface<IWorldTile> GetTile(UBehaviorTreeComponent& OwnerComp) const;
	TSubclassOf<AActor> GetBuildingClass(UBehaviorTreeComponent& OwnerComp) const;
	void SpawnBuilding(UBehaviorTreeComponent& OwnerComp, TScriptInterface<IWorldTile> Tile, TSubclassOf<AActor> BuildingClass) const;
};
