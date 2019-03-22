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
	void SetupWidget(FName RowName, FBuildingData& BuildingData) override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuyClickedSignature, FName, RowName);

	FOnBuyClickedSignature OnBuyClicked;

protected:
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void SpawnBuilding() override;

	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UImage* GetIconWidget() const;

	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UTextBlock* GetNameWidget() const;

	UFUNCTION(Category = Accessors, BlueprintImplementableEvent)
	UTextBlock* GetCostWidget() const;


private:
	UPROPERTY()
	FName BuildingRowName;
};
