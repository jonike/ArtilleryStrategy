// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultPlayerState.h"

bool ADefaultPlayerState::IsEnoughMoney(const int Amount) const
{
	return Money >= Amount;
}

void ADefaultPlayerState::AddMoney(const int Amount)
{
	Money += Amount;
}

void ADefaultPlayerState::RemoveMoney(const int Amount)
{
	check(IsEnoughMoney(Amount));
	Money -= Amount;
}

int ADefaultPlayerState::GetMoneyAmount() const
{
	return Money;
}
