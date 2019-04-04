// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceDeposit.h"

int UResourceDeposit::GetAmount() const
{
	return Amount;
}

const FResource* UResourceDeposit::GetResource() const
{
	return ResourceDepositTable->FindRow<FResource>(ResourceName, TEXT("Get resource of resource deposit object"));
}

FName UResourceDeposit::GetResourceName() const
{
	return ResourceName;
}
