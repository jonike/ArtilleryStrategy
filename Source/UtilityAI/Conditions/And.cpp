// Fill out your copyright notice in the Description page of Project Settings.

#include "And.h"

bool UAnd::EvaluateTwo(const bool FirstResult, const bool SecondResult) const
{
	return FirstResult && SecondResult;
}
