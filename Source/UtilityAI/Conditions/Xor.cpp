// Fill out your copyright notice in the Description page of Project Settings.


#include "Xor.h"

bool UXor::EvaluateTwo(const bool FirstResult, const bool SecondResult) const
{
	return FirstResult && !SecondResult || !FirstResult && SecondResult;
}
