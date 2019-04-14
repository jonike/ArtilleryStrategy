// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHandle.h"

uint32 GetTypeHash(const FResourceHandle& Resource)
{
	return GetTypeHash(Resource.RowName);
}
