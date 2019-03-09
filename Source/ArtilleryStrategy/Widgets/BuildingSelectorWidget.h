// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingSelectorWidget.generated.h"

class UUniformGridPanel;
class UDataTable;

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
	UPROPERTY(Category = Grid, EditDefaultsOnly)
		TSubclassOf<UUserWidget> GridItemWidgetClass;
	UPROPERTY(Category = Gird, EditAnywhere)
		int GridColumns = 3;
};
