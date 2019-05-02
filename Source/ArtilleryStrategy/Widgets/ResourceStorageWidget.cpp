// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorageWidget.h"
#include "Interfaces/PlayerRepository.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/ResourceWidgetInterface.h"

void UResourceStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const auto Wallet = GetWallet();
	if (Wallet)
	{
		auto Index = 0;
		for (const auto& Handle : ResourcesToShow)
		{
			auto ResourceWidget = GetResourceWidget(Index++);
			ResourceWidget->SetupResourceWidget(Handle);
			PlaceResourceWidget(Cast<UUserWidget>(ResourceWidget.GetObject()));
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

TScriptInterface<IPlayerRepository> UResourceStorageWidget::GetWallet() const
{
	return GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>();
}
