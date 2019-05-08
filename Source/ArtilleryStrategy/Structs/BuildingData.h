// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTableEditor/Private/SRowEditor.h"
#include "ResourceHandle.h"
#include "BuildingData.generated.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	Resource,
	Weapon,
	Capital,
};

/**
 *
 */
USTRUCT(BlueprintType)
struct ARTILLERYSTRATEGY_API FBuildingData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FriendlyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MustImplement = "Building"))
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FResourceHandle> Resources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<FString> Tags;
};
