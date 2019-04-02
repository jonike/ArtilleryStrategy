// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"
#include "Objects/ResourceStorage.h"
#include "GameFramework/PlayerState.h"

TScriptInterface<IWallet> UResourceWidget::GetWallet() const
{
	return GetOwningPlayer()->GetPlayerState<APlayerState>();
}

UResourceStorage* UResourceWidget::GetResourceStorage() const
{
	return  GetWallet()->GetResourceWallet();
}
