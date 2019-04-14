// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource.h"

bool operator==(const FResource& Lhs, const FResource& Rhs)
{
	return Lhs.Icon == Rhs.Icon
			&& Lhs.FriendlyName == Rhs.FriendlyName
			&& Lhs.MinAmountSpawned == Rhs.MinAmountSpawned
			&& Lhs.MaxAmountSpawned == Rhs.MaxAmountSpawned
			&& Lhs.BaseCost == Rhs.BaseCost;
}

uint32 GetTypeHash(const FResource& Resource)
{
	return GetTypeHash(Resource.FriendlyName);
}
