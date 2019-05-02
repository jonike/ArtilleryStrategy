// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SelectBuildingClass.generated.h"

class UDataTable;
class IWorldTile;

/**
 * \brief Task that selects building class depending on what resources is available on the given tile
 */
UCLASS()
class ARTILLERYSTRATEGY_API USelectBuildingClass : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USelectBuildingClass();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	virtual void SelectClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IWorldTile>& Tile);

	virtual void SelectMineralBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IWorldTile>& Tile);

	virtual void SelectEnergyBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, const TScriptInterface<IWorldTile>& Tile);

private:
	UPROPERTY(Category = "Input", EditAnywhere)
	UDataTable* Buildings;

	UPROPERTY(Category = "Input", EditAnywhere)
	FBlackboardKeySelector SelectedTile;

	UPROPERTY(Category = "Output", EditAnywhere)
	FBlackboardKeySelector BuildingClass;
};
