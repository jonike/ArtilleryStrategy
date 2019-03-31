// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ResourceWidgetInterface.h"
#include "ResourceWidget.generated.h"

struct FResource;
/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceWidget : public UUserWidget, public IResourceWidgetInterface
{
	GENERATED_BODY()

public:
	void Fill(const FName& Name, const FResource& Resource) override;
};
