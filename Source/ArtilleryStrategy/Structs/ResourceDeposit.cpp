// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDeposit.h"

int UResourceDeposit::GetAmount() const
{
	return Amount;
}

FResource UResourceDeposit::GetResource() const
{
	return Resource;
}

void UResourceDeposit::Setup(FResource* DepositResource, const int ResourceAmount)
{
	check(DepositResource);
	// TODO: avoid copying (potentially large) data
	Resource = *DepositResource;
	Amount = ResourceAmount;
}
