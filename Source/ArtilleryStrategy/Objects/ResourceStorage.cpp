// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Structs/ResourceAmount.h"

void UResourceStorage::AddResource(FResourceAmount ResourceAmount)
{
	if (Storage.Contains(ResourceAmount.Resource))
	{
		Storage[ResourceAmount.Resource] += ResourceAmount.Amount;
		ResourceAmount.Amount = Storage[ResourceAmount.Resource];
	}
	else
	{
		Storage.Add(ResourceAmount.Resource, ResourceAmount.Amount);
	}
	OnResourceAdded.Broadcast(ResourceAmount);
}

void UResourceStorage::SpendResource(FResourceAmount ResourceAmount)
{
	check(IsEnough(ResourceAmount));
	Storage[ResourceAmount.Resource] -= ResourceAmount.Amount;
	ResourceAmount.Amount = Storage[ResourceAmount.Resource];
	OnResourceSpent.Broadcast(ResourceAmount);
}

float UResourceStorage::GetAmount(const FResource& Resource) const
{
	return Storage.Contains(Resource) ? Storage[Resource] : 0.f;
}

bool UResourceStorage::IsEnough(const FResourceAmount& Resource) const
{
	return GetAmount(Resource.Resource) > Resource.Amount;
}
