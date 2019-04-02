// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"

void UResourceStorage::Add(const FName& Resource, const float Amount)
{
	Storage.FindOrAdd(Resource);
	Storage[Resource] += Amount;
}

void UResourceStorage::Spend(const FName& Resource, const float Amount)
{
	Storage.FindOrAdd(Resource);
	Storage[Resource] -= Amount;
}

float UResourceStorage::GetAmount(const FName& Resource) const
{
	return Storage.Contains(Resource) ? Storage[Resource] : 0.f;
}

bool UResourceStorage::IsEnough(const FName& Resource, const float Amount) const
{
	return GetAmount(Resource) >= Amount;
}
