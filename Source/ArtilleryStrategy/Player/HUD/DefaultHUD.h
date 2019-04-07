// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

class UTurnWidget;
class UResourceStorageWidget;
class IGridPlatform;
class ICanBuyBuildings;
class UUserWidget;
class UBuyPlatformWidget;
class UBuildingSelectorWidget;
class ICanBeOwned;
class ICanBuyCells;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowBuyCellWidget(TScriptInterface<ICanBeOwned> Property);
	void ShowBuildingSelectorWidget(TScriptInterface<IGridPlatform> Cell);
	void HideBuyWidget();
	bool IsBuyWidgetsVisible() const;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Category = Widgets, EditAnywhere)
	bool bAutoCloseBuyWidget = true;

	UPROPERTY(Category = Widgets, EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuyCellWidgetClass;
	UPROPERTY(Category = Widgets, EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuildingsSelectorWidgetClass;
	UPROPERTY(Category = Widgets, EditDefaultsOnly)
	TSubclassOf<UUserWidget> ResourceStorageWidgetClass;
	UPROPERTY(Category = "Widgets", EditDefaultsOnly)
	TSubclassOf<UUserWidget> TurnWidgetClass;

	UPROPERTY()
	UBuyPlatformWidget* BuyCellWidget = nullptr;
	UPROPERTY()
	UBuildingSelectorWidget* BuildingSelectorWidget = nullptr;
	UPROPERTY()
	UUserWidget* ActiveBuyWidget = nullptr;
	UPROPERTY()
	UResourceStorageWidget* ResourceStorageWidget = nullptr;
	UPROPERTY()
	UTurnWidget* TurnWidget;

	UFUNCTION()
	void ReceiveOnBuyCellClicked(TScriptInterface<ICanBeOwned> Property);
	UFUNCTION()
	void ReceiveOnBuyBuildingClicked(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass);
	UFUNCTION()
	void ReceiveOnCloseClicked();

	void ShowResourceStorageWidget();
	void HideResourceStorageWidget();
	bool IsResourceStorageWidgetVisible() const;

	void CreateBuyCellWidget();
	void CreateBuildingSelectorWidget();
	void CreateResourceStorageWidget();

	TScriptInterface<ICanBuyCells> GetCellBuyer() const;
	TScriptInterface<ICanBuyBuildings> GetBuildingsBuyer() const;
};
