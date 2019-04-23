// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
// TODO: make class instead of struct
template <typename T>
struct ARTILLERYSTRATEGY_API TValueRange
{
public:
	TValueRange() = default;
	TValueRange(T Min, T Max) : MinValue(Min), MaxValue(Max)
	{
	}

	void SetMin(T Value);
	void SetMax(T Value);

	bool IsInRange(T Value) const;
	bool IsLess(T Value) const;
	bool IsGreater(T Value) const;
	bool IsEmpty() const { return MinValue >= MaxValue; }

	T GetMin() const { return MinValue; }
	T GetMax() const { return MaxValue; }

private:
	T MinValue{};
	T MaxValue{};
};

template <typename T>
void TValueRange<T>::SetMin(T Value)
{
	MinValue = Value;
}

template <typename T>
void TValueRange<T>::SetMax(T Value)
{
	MaxValue = Value;
}

template <typename T>
bool TValueRange<T>::IsInRange(T Value) const
{
	return GetMin() <= Value && Value <= GetMax();
}

template <typename T>
bool TValueRange<T>::IsLess(T Value) const
{
	return Value < GetMin() && Value < GetMax();
}

template <typename T>
bool TValueRange<T>::IsGreater(T Value) const
{
	return Value > GetMax() && Value > GetMin();
}
