// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"
#include "BehaviorTree/BehaviorTree.h"

void ADefaultAIController::BeginPlay()
{
	Super::BeginPlay();	
	UseBlackboard(BlackboardData, Blackboard);
	RunBehaviorTree(TurnBehavior);
}
