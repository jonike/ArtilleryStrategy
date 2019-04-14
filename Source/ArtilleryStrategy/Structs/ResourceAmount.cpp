// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceAmount.h"

const FResource& FResourceAmount::GetResource(const FString& Context) const
{
	const auto Result = ResourceHandle.GetRow<FResource>(Context);
	check(Result);
	return *Result;
}

bool operator==(const FResourceAmount& Lhs, const FResourceAmount& Rhs)
{
	return Lhs.Amount == Rhs.Amount && Lhs.ResourceHandle == Rhs.ResourceHandle;
}

uint32 GetTypeHash(const FResourceAmount& ResourceAmount)
{
	return GetTypeHash(ResourceAmount.ResourceHandle);
}

const FResource& FResourceAmount::GetResource(const TCHAR* Context) const
{
	const auto Result = ResourceHandle.GetRow<FResource>(Context);
	check(Result);
	return *Result;
}
