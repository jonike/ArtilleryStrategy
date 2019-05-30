// Fill out your copyright notice in the Description page of Project Settings.


#include "Unary.h"

bool UUnary::EvaluateOne(bool Result) const
{
	return false;
}

bool UUnary::EvaluateRaw() const
{
	return Condition && EvaluateOne(Condition->Evaluate());
}
