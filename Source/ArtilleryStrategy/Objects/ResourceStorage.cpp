// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Objects/ResourceDeposit.h"

void UResourceStorage::Add(UResourceDeposit* Resource)
{
	const auto& Name = Resource->GetResource().FriendlyName;
	Storage.FindOrAdd(Name);
	Storage[Name] += Resource->GetAmount();
}

void UResourceStorage::Spend(UResourceDeposit* Resource)
{
	const auto& Name = Resource->GetResource().FriendlyName;
	Storage.FindOrAdd(Name);
	Storage[Name] -= Resource->GetAmount();
}

float UResourceStorage::GetAmount(UResourceDeposit* Resource) const
{
	const auto& Name = Resource->GetResource().FriendlyName;
	return Storage.Contains(Name) ? Storage[Name]->GetAmount() : 0.f;
}

bool UResourceStorage::IsEnough(UResourceDeposit* Resource, float Amount) const
{
	return GetAmount(Resource) >= Amount;
}
