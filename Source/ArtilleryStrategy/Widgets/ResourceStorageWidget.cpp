// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorageWidget.h"
#include "Interfaces/Wallet.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/ResourceWidgetInterface.h"

void UResourceStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ResourcesTable)
	{
		const auto Wallet = GetWallet();
		if (Wallet)
		{
			const auto& Names = ResourcesTable->GetRowNames();
			for (auto i = 0; i < Names.Num(); ++i)
			{
				auto ResourceWidget = GetResourceWidget(i);
				const auto ResourceData = ResourcesTable->FindRow<FResource>(Names[i], TEXT("Filling resource storage widget"));
				ResourceWidget->Fill(Names[i], *ResourceData);
				PlaceResourceWidget(Cast<UUserWidget>(ResourceWidget.GetObject()));
			}
		}
	}
}

TScriptInterface<IResourceWidgetInterface> UResourceStorageWidget::GetResourceWidget(const int Index)
{
	if (ResourceWidgets.IsValidIndex(Index))
	{
		return ResourceWidgets[Index];
	}
	const auto ResourceWidget = CreateWidget<UUserWidget>(GetOwningPlayer(), ResourceWidgetClass);
	ResourceWidgets.Add(ResourceWidget);
	return ResourceWidget;
}

TScriptInterface<IWallet> UResourceStorageWidget::GetWallet() const
{
	return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
}
