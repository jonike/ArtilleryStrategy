// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSelectorWidget.generated.h"

class UUniformGridPanel;
class UDataTable;
class IBuildingGridItemWidget;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API UBuildingSelectorWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = Grid)
		void FillBuildingsData(UUniformGridPanel* GridPanel);

private:
	UPROPERTY(Category = Grid, EditAnywhere)
		UDataTable* BuildingsDataTable;
	UPROPERTY(Category = Grid, EditDefaultsOnly, meta = (MustImplement = "BuildingGridItemWidget"))
		TSubclassOf<UUserWidget> GridItemWidgetClass;
	UPROPERTY(Category = Gird, EditAnywhere)
		int GridColumns = 3;

	TArray<IBuildingGridItemWidget*> GridItemWidgets;

	void AddGridItemWidget(FName RowName, int Number, UUniformGridPanel& GridPanel);
	IBuildingGridItemWidget& LoadOrCreateGridItem(int i);
};
