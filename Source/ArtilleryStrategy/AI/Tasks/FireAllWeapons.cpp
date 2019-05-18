// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAllWeapons.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/WeaponBuilding.h"
#include "Engine/World.h"

UFireAllWeapons::UFireAllWeapons()
{
	TargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UFireAllWeapons, TargetKey), UObject::StaticClass());
	TargetKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFireAllWeapons, TargetKey));
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
					RotateWeapon(Building);
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

void UFireAllWeapons::RotateWeapon(TScriptInterface<IWeaponBuilding> Weapon) const
{
	if (Weapon)
	{
		const auto Target = FVector(0.f, 0.f, 0.f);
		const auto WeaponAsActor = Cast<AActor>(Weapon.GetObject());
		check(WeaponAsActor);
		const auto Offset = Target - WeaponAsActor->GetActorLocation();
		// TODO: remove radians to degrees conversion
		const auto HorizonAngle = FMath::RadiansToDegrees(Offset.HeadingAngle());
		Weapon->SetHorizonAngle(30.f);
		Weapon->SetPlaneAngle(HorizonAngle);
	}
}
