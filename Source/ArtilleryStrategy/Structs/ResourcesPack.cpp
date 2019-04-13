// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourcePack.h"

bool FResourcePack::ContainsEqualResourcePack(const FResourcePack& Other) const
{
	return Resources.Difference(Other.Resources).Num() == 0 && Other.Resources.Difference(Resources).Num() == 0;
}
