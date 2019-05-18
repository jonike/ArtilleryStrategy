// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AttackTargets.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UAttackTargets : public UObject
{
	GENERATED_BODY()

public:
	void Add(AActor* Target);

	const TSet<AActor*>& GetTargets() const;

private:
	// TODO: null pointers accumulation is imminent; add mechanism to remove pointers to destroyed objects
	UPROPERTY(VisibleInstanceOnly)
	TSet<AActor*> Targets;
};
