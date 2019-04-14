// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Structs/ResourceAmount.h"

void UResourceStorage::AddResource(FResourceAmount ResourceAmount)
{
	if (Storage.Contains(ResourceAmount.ResourceHandle))
	{
		Storage[ResourceAmount.ResourceHandle] += ResourceAmount.Amount;
		ResourceAmount.Amount = Storage[ResourceAmount.ResourceHandle];
	}
	else
	{
		Storage.Add(ResourceAmount.ResourceHandle, ResourceAmount.Amount);
	}
	OnResourceAdded.Broadcast(ResourceAmount);
}

void UResourceStorage::SpendResource(FResourceAmount ResourceAmount)
{
	check(IsEnough(ResourceAmount));
	Storage[ResourceAmount.ResourceHandle] -= ResourceAmount.Amount;
	ResourceAmount.Amount = Storage[ResourceAmount.ResourceHandle];
	OnResourceSpent.Broadcast(ResourceAmount);
}

float UResourceStorage::GetAmount(const FResourceHandle& Resource) const
{
	return Storage.Contains(Resource) ? Storage[Resource] : 0.f;
}

bool UResourceStorage::IsEnough(const FResourceAmount& Resource) const
{
	return GetAmount(Resource.ResourceHandle) > Resource.Amount;
}
