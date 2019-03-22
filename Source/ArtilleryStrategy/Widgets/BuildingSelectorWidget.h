// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSelectorWidget.generated.h"

class UUniformGridPanel;
class UDataTable;
class IBuildingGridItemWidget;
class IGridPlatform;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuildingSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetSelectedPlatform(TScriptInterface<IGridPlatform> Selected);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseClickedSignature);

	FOnCloseClickedSignature OnCloseClicked;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuyClickedSignature, TScriptInterface<IGridPlatform>, Cell,
												TSubclassOf<AActor>, BuildingClass);

	FOnBuyClickedSignature OnBuyClicked;

protected:
	UFUNCTION(BlueprintCallable, Category = Grid)
	void FillBuildingsData(UUniformGridPanel* GridPanel);

	UFUNCTION(BlueprintCallable, Category = Closing)
	void CloseWidget() const;

private:
	UPROPERTY(Category = Grid, EditAnywhere)
	UDataTable* BuildingsDataTable;
	UPROPERTY(Category = Grid, EditDefaultsOnly, meta = (MustImplement = "BuildingGridItemWidget"))
	TSubclassOf<UUserWidget> GridItemWidgetClass;
	UPROPERTY(Category = Gird, EditAnywhere)
	int GridColumns = 3;

	TArray<TScriptInterface<IBuildingGridItemWidget>> GridItemWidgets;
	TScriptInterface<IGridPlatform> SelectedPlatform;

	UFUNCTION()
	void WhenBuyClicked(FName BuildingName);

	void AddGridItemWidget(FName RowName, int Number, UUniformGridPanel& GridPanel);
	TScriptInterface<IBuildingGridItemWidget> LoadOrCreateGridItem(int i);
};
