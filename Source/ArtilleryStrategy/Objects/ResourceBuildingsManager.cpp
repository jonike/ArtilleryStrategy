// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceBuildingsManager.h"
#include "Interfaces/ResourceBuilding.h"
#include "GameFramework/PlayerController.h"

void UResourceBuildingsManager::AddResourceBuilding(TScriptInterface<IResourceBuilding> Building)
{
	check(Building);
	ResourceBuildings.Add(Building);
}
