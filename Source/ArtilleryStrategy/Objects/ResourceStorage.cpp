// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceStorage.h"
#include "Structs/ResourceAmount.h"

void UResourceStorage::AddResource(FResourceAmount& Resource)
{
	//if (Storage.Contains(Resource))
	//{
	//	const auto Index = Storage.Find(Resource);
	//	// TODO: add resource
	//}
	//else
	//{
	//	Storage.Add(Resource);
	//}
	//OnResourceAdded.Broadcast();
}

void UResourceStorage::SpendResource(FResourceAmount& Resource)
{
	//if (Storage.Contains(Resource))
	//{
	//	const auto Index = Storage.Find(Resource);
	//	// TODO: spend resource
	//	OnResourceSpent.Broadcast();
	//}
	// TODO: check if there is no or not enough resource
}

float UResourceStorage::GetAmount(FResource& Resource) const
{
	/*const auto Index = Storage.FindByPredicate([](const FResourceAmount & ResourceAmount) { return ResourceAmount.Resource == Resource; });
	return Storage.IsValidIndex(Index) ? Storage[Index].Amount : 0.f;*/
	return 0.f;
}

bool UResourceStorage::IsEnough(FResourceAmount& Resource) const
{
	/*return GetAmount(Resource) >= Amount;*/
	return false;
}
