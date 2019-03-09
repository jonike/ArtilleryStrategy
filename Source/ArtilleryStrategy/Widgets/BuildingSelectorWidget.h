// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Building.h"
#include "BuildingSelectorWidget.generated.h"

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuildingSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void FillBuildingsData();

private:
	UPROPERTY(Category = Buildings, EditAnywhere)
		TSet<TSubclassOf<IBuilding>> BuildingClasses;
};
