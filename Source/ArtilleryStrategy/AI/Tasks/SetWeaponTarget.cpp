// Fill out your copyright notice in the Description page of Project Settings.

#include "SetWeaponTarget.h"
#include "Interfaces/PlayerProperty.h"
#include "Interfaces/WeaponBuilding.h"
#include "Interfaces/WorldTile.h"
#include "Libraries/EnemiesLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

USetWeaponTarget::USetWeaponTarget()
{
	WeaponKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USetWeaponTarget, WeaponKey), UPlayerProperty::StaticClass());
	WeaponKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USetWeaponTarget, WeaponKey), UWeaponBuilding::StaticClass());

	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USetWeaponTarget, TargetKey), UPlayerProperty::StaticClass());
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USetWeaponTarget, TargetKey), UWorldTile::StaticClass());
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(USetWeaponTarget, TargetKey), AActor::StaticClass());
}

EBTNodeResult::Type USetWeaponTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto Targets = UEnemiesLibrary::GetAttackTargets(OwnerComp.GetAIOwner()))
	{
		if (const auto Target = SelectTarget(OwnerComp, Targets))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, Target);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type USetWeaponTarget::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void USetWeaponTarget::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

AActor* USetWeaponTarget::SelectTarget(const UBehaviorTreeComponent& OwnerComp, UAttackTargets* Targets) const
{
	if (Targets->GetTargets().Num() == 0)
	{
		return nullptr;
	}
	const auto& TargetsAsArray = Targets->GetTargets();
	const auto Index = FMath::RandRange(0, TargetsAsArray.Num() - 1);
	return TargetsAsArray[Index];
}
