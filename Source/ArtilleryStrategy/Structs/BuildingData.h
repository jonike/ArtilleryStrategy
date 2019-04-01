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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName FriendlyName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "Building"))
		TSubclassOf<AActor> SpawnClass;
};
