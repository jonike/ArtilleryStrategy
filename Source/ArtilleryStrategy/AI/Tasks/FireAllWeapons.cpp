// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAllWeapons.h"
#include "AIController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Interfaces/WeaponBuilding.h"

UFireAllWeapons::UFireAllWeapons()
{
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
				if (const auto BuildingAsWeapon = Cast<IWeaponBuilding>(Building))
				{
					if (BuildingAsWeapon->IsReadyForFire())
					{
						BuildingAsWeapon->Fire();
					}
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
