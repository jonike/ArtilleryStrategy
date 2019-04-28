// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SelectBuildingClass.generated.h"

/**
 *
 */
UCLASS(Abstract)
class ARTILLERYSTRATEGY_API USelectBuildingClass : public UBTTaskNode
{
	GENERATED_BODY()

public:
	USelectBuildingClass();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	virtual void SelectClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, TScriptInterface<IGridPlatform> Tile);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual void SelectMineralBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, TScriptInterface<ICanBeOwned> Tile);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	virtual void SelectEnegryBuildingClass(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, TScriptInterface<ICanBeOwned> Tile);

private:
	UPROPERTY(Category = "Input", EditAnywhere)
	FBlackboardKeySelector SelectedTile;

	UPROPERTY(Category = "Output", EditAnywhere)
	FBlackboardKeySelector BuildingClass;
};
