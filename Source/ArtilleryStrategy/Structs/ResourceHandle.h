// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ResourceHandle.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FResourceHandle : public FDataTableRowHandle
{
	GENERATED_BODY()

	operator bool() const;
};

uint32 GetTypeHash(const FResourceHandle& Resource);
