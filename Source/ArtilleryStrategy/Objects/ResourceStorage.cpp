// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Structs/ResourceAmount.h"

void UResourceStorage::AddResource(FResourceAmount& Resource)
{
	if (Storage.Contains(Resource.Resource))
	{
		Storage[Resource.Resource] += Resource.Amount;
	}
	else
	{
		Storage.Add(Resource.Resource, Resource.Amount);
	}
	OnResourceAdded.Broadcast();
}

void UResourceStorage::SpendResource(FResourceAmount& Resource)
{
	check(IsEnough(Resource));
	Storage[Resource.Resource] -= Resource.Amount;
	OnResourceSpent.Broadcast();
}

float UResourceStorage::GetAmount(FResource& Resource) const
{
	return Storage.Contains(Resource) ? Storage[Resource] : 0.f;
}

bool UResourceStorage::IsEnough(FResourceAmount& Resource) const
{
	return GetAmount(Resource.Resource) > Resource.Amount;
}
