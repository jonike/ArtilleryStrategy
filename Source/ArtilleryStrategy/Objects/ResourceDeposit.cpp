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

void UResourceDeposit::Setup(FResource* Resource, const int Amount)
{
	check(Resource);
	// TODO: avoid copying (potentially large) data
	this->Resource = *Resource;
	this->Amount = Amount;
}
