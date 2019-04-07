// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/TurnDependent.h"
#include "TurnWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UTurnWidget : public UUserWidget, public ITurnDependent
{
	GENERATED_BODY()

protected:
	UFUNCTION(Category = "Turn", BlueprintCallable)
	void EndTurn();
};
