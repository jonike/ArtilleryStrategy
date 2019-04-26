// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Player/States/DefaultPlayerState.h"

UMaterialInterface* ADefaultAIController::GetOwnerMaterial() const
{
	return OwnerMaterial;
}

UTexture2D* ADefaultAIController::GetOwnerIcon() const
{
	return OwnerIcon;
}

TScriptInterface<IWallet> ADefaultAIController::GetWallet() const
{
	return GetPlayerState<ADefaultPlayerState>();
}

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();	
	UseBlackboard(BlackboardData, Blackboard);
	RunBehaviorTree(TurnBehavior);
}
