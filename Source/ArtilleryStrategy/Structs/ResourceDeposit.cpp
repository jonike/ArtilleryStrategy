// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDeposit.h"

bool operator==(const FResourceDeposit& Lhs, const FResourceDeposit& Rhs)
{
	return Lhs.ResourceAmount == Rhs.ResourceAmount;
}

uint32 GetTypeHash(const FResourceDeposit& ResourceDeposit)
{
	return GetTypeHash(ResourceDeposit.ResourceAmount);
}
