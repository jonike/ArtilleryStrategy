// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceWidget.h"

TScriptInterface<IWallet> UResourceWidget::GetWallet() const
{
	return GetOwningPlayer()->GetPlayerState<APlayerState>();
}
