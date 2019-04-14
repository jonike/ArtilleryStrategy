// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Objects/ResourceStorage.h"
#include "GameFramework/PlayerState.h"
#include "ScriptInterface.h"

void UResourceWidget::SetupResourceWidget(const FResourceHandle Resource)
{
	ShowedResource = Resource;
	GetWallet()->GetResourceWallet()->OnResourceAdded.AddDynamic(this, &UResourceWidget::ReceiveOnResourceAmountChanged);
	GetWallet()->GetResourceWallet()->OnResourceSpent.AddDynamic(this, &UResourceWidget::ReceiveOnResourceAmountChanged);
	FillResourceWidget(Resource);
}

TScriptInterface<IWallet> UResourceWidget::GetWallet() const
{
	return GetOwningPlayer()->GetPlayerState<APlayerState>();
}

UResourceStorage* UResourceWidget::GetResourceStorage() const
{
	return  GetWallet()->GetResourceWallet();
}

void UResourceWidget::ReceiveOnResourceAmountChanged(const FResourceAmount& Resource)
{
	if (ShowedResource == Resource.ResourceHandle)
	{
		UpdateResourceAmount(Resource);
	}
}
