// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Structs/ResourceDeposit.h"

void UResourceStorage::Add(FResourceDeposit& Resource)
{
	if (Storage.Contains(Resource))
	{
		const auto Index = Storage.Find(Resource);
		// TODO: add resource
	}
	else
	{
		Storage.Add(Resource);
	}
	OnResourceAdded.Broadcast();
}

void UResourceStorage::Spend(FResourceDeposit& Resource, float Amount)
{
	if (Storage.Contains(Resource))
	{
		const auto Index = Storage.Find(Resource);
		// TODO: spend resource
		OnResourceSpent.Broadcast();
	}
	// TODO: check if there is no or not enough resource
}

float UResourceStorage::GetAmount(FResourceDeposit& Resource) const
{
	const auto Index = Storage.Find(Resource);
	return Storage.IsValidIndex(Index) ? Storage[Index].ResourceAmount.Amount : 0.f;
}

bool UResourceStorage::IsEnough(FResourceDeposit& Resource, const float Amount) const
{
	return GetAmount(Resource) >= Amount;
}
