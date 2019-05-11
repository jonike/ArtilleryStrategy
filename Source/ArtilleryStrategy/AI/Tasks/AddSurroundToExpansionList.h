// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AddSurroundToExpansionList.generated.h"

class IWorldTile;
class UExpansionPreferences;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UAddSurroundToExpansionList : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UAddSurroundToExpansionList();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void OnGameplayTaskActivated(UGameplayTask& Task) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TileKey;

	UExpansionPreferences* GetExpansionPreferences(UBehaviorTreeComponent& OwnerComp) const;

	TScriptInterface<IWorldTile> UnpackTile(UBehaviorTreeComponent& OwnerComp) const;

	bool CheckIfNeedsToAdd(UBehaviorTreeComponent& OwnerComp, TScriptInterface<IWorldTile> Tile) const;
};
