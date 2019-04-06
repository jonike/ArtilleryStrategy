// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseResourceBuilding.h"

bool ABaseResourceBuilding::IsProducingResource() const
{
	return ProducedResource != nullptr;
}

void ABaseResourceBuilding::AddResourceDeposit(UResourceDeposit* Deposit)
{
	ProducedResource = Deposit;
}

UResourceDeposit* ABaseResourceBuilding::GetProducingResource() const
{
	return ProducedResource;
}
