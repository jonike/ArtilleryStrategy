// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorageWidget.h"
#include "Interfaces/Wallet.h"
#include "GameFramework/PlayerState.h"

void UResourceStorageWidget::NativeConstruct()
{
	if (ResourcesTable)
	{
		const auto Wallet = GetWallet();
	}
}

TScriptInterface<IWallet> UResourceStorageWidget::GetWallet() const
{
	return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
}
