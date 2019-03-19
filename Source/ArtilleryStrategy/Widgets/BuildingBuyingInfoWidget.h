// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Image.h"
#include "TextBlock.h"
#include "Interfaces/BuildingGridItemWidget.h"
#include "BuildingBuyingInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuildingBuyingInfoWidget : public UUserWidget, public IBuildingGridItemWidget
{
	GENERATED_BODY()

public:
	void Setup(FBuildingData& BuildingData) override;

	void SpawnBuilding() override;

protected:
	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UImage* GetIconWidget() const;

	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UTextBlock* GetNameWidget() const;

	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UTextBlock* GetCostWidget() const;
};
