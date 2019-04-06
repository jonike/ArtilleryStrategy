// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Objects/ResourceDeposit.h"

void UResourceStorage::Add(UResourceDeposit* Resource)
{
	const auto& Name = Resource->GetResource().FriendlyName;
	Storage.Add(Name);
	Storage[Name] += Resource->GetAmount();
	OnResourceAdded.Broadcast();
}

void UResourceStorage::Spend(UResourceDeposit* Resource, float Amount)
{
	const auto& Name = Resource->GetResource().FriendlyName;
	check(IsEnough(Resource, Amount));
	Storage[Name] -= Resource->GetAmount();
	OnResourceSpent.Broadcast();
}

float UResourceStorage::GetAmount(UResourceDeposit* Resource) const
{
	const auto& Name = Resource->GetResource().FriendlyName;
	return Storage.Contains(Name) ? Storage[Name]->GetAmount() : 0.f;
}

float UResourceStorage::GetAmountByName(const FName Resource) const
{
	return Storage.Contains(Resource) ? Storage[Resource]->GetAmount() : 0.f;
}

bool UResourceStorage::IsEnough(UResourceDeposit* Resource, float Amount) const
{
	return GetAmount(Resource) >= Amount;
}
