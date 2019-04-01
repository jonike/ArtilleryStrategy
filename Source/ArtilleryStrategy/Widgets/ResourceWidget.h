// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/ResourceWidgetInterface.h"
#include "Structs/Resource.h"
#include "IUserObjectListEntry.h"
#include "ResourceWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTILLERYSTRATEGY_API UResourceWidget : public UUserWidget, public IResourceWidgetInterface, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = Initialization, BlueprintImplementableEvent)
	void Fill(const FName& Name, const FResource& Resource) override;
};
