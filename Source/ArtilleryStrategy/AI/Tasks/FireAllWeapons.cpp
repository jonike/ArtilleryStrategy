// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAllWeapons.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/WeaponBuilding.h"
#include "Engine/World.h"
#include "Curves/CurveFloat.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/WorldTile.h"

UFireAllWeapons::UFireAllWeapons()
{
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFireAllWeapons, TargetKey), AActor::StaticClass());
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFireAllWeapons, TargetKey), UPlayerProperty::StaticClass());
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFireAllWeapons, TargetKey), UWorldTile::StaticClass());

}

EBTNodeResult::Type UFireAllWeapons::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const auto State = OwnerComp.GetAIOwner()->GetPlayerState<APlayerState>())
	{
		if (const auto DefaultState = Cast<ADefaultPlayerState>(State))
		{
			const auto OwnedBuildings = DefaultState->GetOwnedBuildings();
			for (const auto& Building : OwnedBuildings)
			{
				if (Cast<IWeaponBuilding>(Building))
				{
					const auto Target = UnpackTarget(OwnerComp);
					RotateWeapon(Building, Target);
					FireWeapon(Building);
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UFireAllWeapons::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Aborted;
}

void UFireAllWeapons::OnGameplayTaskActivated(UGameplayTask& Task)
{
}

void UFireAllWeapons::FireWeapon(TScriptInterface<IWeaponBuilding> Weapon) const
{
	if (Weapon)
	{
		if (Weapon->IsReadyForFire())
		{
			Weapon->Fire();
		}
	}
}

TPair<float, float> UFireAllWeapons::GetWeaponAngles(const TScriptInterface<IWeaponBuilding> Weapon, const FVector& Target) const
{
	const auto WeaponAsActor = Cast<AActor>(Weapon.GetObject());
	check(WeaponAsActor);
	const auto Offset = Target - WeaponAsActor->GetActorLocation();
	// TODO: remove radians to degrees conversion
	const auto PlaneAngle = FMath::RadiansToDegrees(Offset.HeadingAngle());
	const auto Distance = Offset.Size();
	const auto HorizonAngle = AngleCurve->GetFloatValue(Distance);
	return MakeTuple(PlaneAngle, HorizonAngle);
}

FVector UFireAllWeapons::UnpackTarget(UBehaviorTreeComponent& OwnerComp) const
{
	const auto Object = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey.SelectedKeyName);
	const auto Actor = Cast<AActor>(Object);
	check(Actor);
	return Actor->GetActorLocation();
}

void UFireAllWeapons::RotateWeapon(TScriptInterface<IWeaponBuilding> Weapon, const FVector& Target) const
{
	if (Weapon)
	{
		const auto Angles = GetWeaponAngles(Weapon, Target);
		Weapon->SetPlaneAngle(Angles.Get<0>());
		Weapon->SetHorizonAngle(Angles.Get<1>());
	}
}
