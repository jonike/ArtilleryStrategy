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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseClickedSignature);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuyClickedSignature, TScriptInterface<IGridPlatform>, Cell, TSubclassOf<AActor>, BuildingClass);

public:
	void SetSelectedPlatform(TScriptInterface<IGridPlatform> Selected);

	FOnBuyClickedSignature OnBuyClicked;
	FOnCloseClickedSignature OnCloseClicked;

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
	void ReceiveOnBuyClicked(FName BuildingName);

	void AddItemWidget(FName RowName, int Number, UUniformGridPanel* GridPanel);
	void SetPositionInGrid(UUserWidget* ItemWidget, int Number);
	void AddWidgetToGrid(TScriptInterface<IBuildingGridItemWidget> GridItemWidget, UUniformGridPanel* GridPanel, int Number);
	TScriptInterface<IBuildingGridItemWidget> LoadOrCreateGridItem(int Index);
};
