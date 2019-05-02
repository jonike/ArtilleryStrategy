// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

class UPlayerTurnLimitsWidget;
class UTurnWidget;
class UResourceStorageWidget;
class IWorldTile;
class ICanBuyBuildings;
class UUserWidget;
class UBuyPlatformWidget;
class UBuildingSelectorWidget;
class IPlayerProperty;
class ICanBuyTiles;

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowBuyCellWidget(TScriptInterface<IPlayerProperty> Property);
	void ShowBuildingSelectorWidget(TScriptInterface<IWorldTile> Cell);
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
	UPROPERTY(Category = "Widgets", EditDefaultsOnly)
	TSubclassOf<UUserWidget> PlayerTurnLimitsWidgetClass;

	UPROPERTY()
	UBuyPlatformWidget* BuyCellWidget;
	UPROPERTY()
	UBuildingSelectorWidget* BuildingSelectorWidget;
	UPROPERTY()
	UUserWidget* ActiveBuyWidget = nullptr;
	UPROPERTY()
	UResourceStorageWidget* ResourceStorageWidget;
	UPROPERTY()
	UTurnWidget* TurnWidget;
	UPROPERTY()
	UPlayerTurnLimitsWidget* PlayerTurnLimitsWidget;

	UFUNCTION()
	void ReceiveOnBuyCellClicked(TScriptInterface<IPlayerProperty> Property);
	UFUNCTION()
	void ReceiveOnBuyBuildingClicked(TScriptInterface<IWorldTile> Cell, TSubclassOf<AActor> BuildingClass);
	UFUNCTION()
	void ReceiveOnCloseClicked();

	void ShowResourceStorageWidget();
	void HideResourceStorageWidget();
	bool IsResourceStorageWidgetVisible() const;

	void CreateBuyCellWidget();
	void CreateBuildingSelectorWidget();
	void CreateResourceStorageWidget();

	TScriptInterface<ICanBuyTiles> GetCellBuyer() const;
	TScriptInterface<ICanBuyBuildings> GetBuildingsBuyer() const;
};
