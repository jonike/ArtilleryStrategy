// Fill out your copyright notice in the Description page of Project Settings.

#include "Condition.h"

bool UCondition::Evaluate() const
{
	return EvaluateRaw() ^ bInvert;
}

bool UCondition::EvaluateRaw() const
{
	return false;
}
