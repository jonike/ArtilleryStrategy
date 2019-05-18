// Fill out your copyright notice in the Description page of Project Settings.

#include "ArtilleryStrategyGMB.h"
#include "Player/Controllers/DefaultPlayerController.h"
#include "Player/States/DefaultPlayerState.h"
#include "Player/HUD/DefaultHUD.h"
#include "Game/States/DefaultGS.h"
#include "PropertyEditor/Public/PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Customizations/ResourceHandleCustomization.h"
#include "Engine/World.h"

AArtilleryStrategyGMB::AArtilleryStrategyGMB()
{
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
	PlayerStateClass = ADefaultPlayerState::StaticClass();
	HUDClass = ADefaultHUD::StaticClass();
	GameStateClass = ADefaultGS::StaticClass();

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout("ResourceHandle", FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FResourceHandleCustomizationLayout::MakeInstance));
}

void AArtilleryStrategyGMB::BeginPlay()
{
	for (auto i = 0; i < AIPlayers; ++i)
	{
		GetWorld()->SpawnActor(AIActorClass);
	}
}
