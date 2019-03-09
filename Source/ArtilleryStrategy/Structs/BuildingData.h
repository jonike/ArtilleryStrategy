// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditor/Private/SRowEditor.h"
#include "BuildingData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FBuildingData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere)
		FName FriendlyName;
	UPROPERTY(EditAnywhere)
		int Cost;
	UPROPERTY(EditAnywhere, meta = (MustImplement = "Building"))
		TSubclassOf<AActor> SpawnClass;
};
