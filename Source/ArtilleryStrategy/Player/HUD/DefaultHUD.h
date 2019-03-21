// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

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
	void ShowBuyCellWidget(ICanBeOwned& Property);
	void ShowBuildingSelectorWidget();
	void HideBuyWidget();
	bool IsBuyWidgetsVisible() const;

private:
	UPROPERTY(Category = Widgets, EditAnywhere)
	bool bAutoCloseBuyWidget = true;

	UPROPERTY(Category = Widgets, EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuyCellWidgetClass;
	UPROPERTY(Category = Widgets, EditDefaultsOnly)
	TSubclassOf<UUserWidget> BuildingsSelectorWidgetClass;

	UPROPERTY()
	UBuyPlatformWidget* BuyCellWidget = nullptr;
	UPROPERTY()
	UBuildingSelectorWidget* BuildingSelectorWidget = nullptr;
	UPROPERTY()
	UUserWidget* ActiveBuyWidget = nullptr;

	UFUNCTION()
	void WhenBuyClicked(TScriptInterface<ICanBeOwned> Property);
	UFUNCTION()
	void WhenCloseClicked();

	void CreateBuyCellWidget();
	void CreateBuildingSelectorWidget();
	bool IsBuyCellWidgetActive() const;
	ICanBuyCells& GetBuyer() const;
};
