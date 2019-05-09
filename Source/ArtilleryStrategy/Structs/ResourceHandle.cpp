// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHandle.h"

FResourceHandle::operator bool() const
{
	return DataTable && !RowName.IsNone();
}

uint32 GetTypeHash(const FResourceHandle& Resource)
{
	return GetTypeHash(Resource.RowName);
}
