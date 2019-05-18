// Fill out your copyright notice in the Description page of Project Settings.

#include "MarkBuildingsInAreaForAttack.h"
#include "Interfaces/WorldTile.h"
#include "AI/Controllers/AdvancedAIController.h"
#include "Libraries/Tiles.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Objects/AttackTargets.h"

UMarkBuildingsInAreaForAttack::UMarkBuildingsInAreaForAttack()
{
	CenterTileKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UMarkBuildingsInAreaForAttack, CenterTileKey), UWorldTile::StaticClass());
}

EBTNodeResult::Type UMarkBuildingsInAreaForAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Targets = GetAttackTargets(OwnerComp))
	{
		if (const auto Center = OwnerComp.GetBlackboardComponent()->GetValueAsObject(CenterTileKey.SelectedKeyName))
		{
			const auto BuildingsNearby = UTiles::GetBuildingsInRadius(Center, Radius);
			for (const auto& Building : BuildingsNearby)
			{
				if (const auto BuildingAsActor = Cast<AActor>(Building.GetObject()))
				{
					Targets->Add(BuildingAsActor);
				}
			}
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UMarkBuildingsInAreaForAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UMarkBuildingsInAreaForAttack::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

UAttackTargets* UMarkBuildingsInAreaForAttack::GetAttackTargets(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (const auto AdvancedController = Cast<AAdvancedAIController>(Controller))
	{
		return AdvancedController->GetAttackTargets();
	}
	return nullptr;
}
