// Fill out your copyright notice in the Description page of Project Settings.


#include "ValueLimit.h"

FValueLimit::FValueLimit(const int MaxValue) : MaxValue(MaxValue)
{
}

FValueLimit::FValueLimit(const int Value, const int MaxValue) : Value(Value), MaxValue(MaxValue)
{
}

void FValueLimit::Increment()
{
	check(!IsLimitReached());
	++Value;
}

void FValueLimit::Reset()
{
	Value = 0;
}

bool FValueLimit::IsLimitReached() const
{
	return Value >= MaxValue;
}
