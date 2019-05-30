// Fill out your copyright notice in the Description page of Project Settings.

#include "Binary.h"

bool UBinary::EvaluateRaw() const
{
	return First && Second && EvaluateTwo(First->Evaluate(), Second->Evaluate());
}

bool UBinary::EvaluateTwo(bool FirstResult, bool SecondResult) const
{
	return false;
}
