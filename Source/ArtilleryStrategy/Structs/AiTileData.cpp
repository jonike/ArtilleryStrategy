// Fill out your copyright notice in the Description page of Project Settings.

#include "AiTileData.h"

bool operator==(const FAiTileData& Lhs, const FAiTileData& Rhs)
{
	return Lhs.Tile == Rhs.Tile;
}
