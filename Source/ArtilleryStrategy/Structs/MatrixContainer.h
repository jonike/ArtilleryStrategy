// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

/**
 * 
 */
template <typename T>
struct ARTILLERYSTRATEGY_API TMatrixContainer
{
public:
	void Resize(int Rows, int Columns);

	int GetRows() const;
	int GetColumns() const;
	bool IsValidIndex(int Row, int Column) const;
	bool Empty() const;

	T& Get(int Row, int Column);
	const T& Get(int Row, int Column) const;

	T& operator()(int Row, int Column);
	const T& operator()(int Row, int Column) const;

private:
	TArray<TArray<T>> Matrix;
};

template <typename T>
void TMatrixContainer<T>::Resize(int Rows, int Columns)
{
	Matrix.SetNum(Rows);
	for (auto& Row : Matrix)
	{
		Row.SetNum(Columns);
	}
}

template <typename T>
int TMatrixContainer<T>::GetRows() const
{
	return Matrix.Num();
}

template <typename T>
int TMatrixContainer<T>::GetColumns() const
{
	if (GetRows() == 0)
	{
		return 0;
	}
	return Matrix[0].Num();
}

template <typename T>
bool TMatrixContainer<T>::IsValidIndex(int Row, int Column) const
{
	if (!Matrix.IsValidIndex(Row))
	{
		return false;
	}
	return Matrix[Row].IsValidIndex(Column);
}

template <typename T>
bool TMatrixContainer<T>::Empty() const
{
	return Matrix.Num() == 0 || Matrix[0].Num() == 0;
}

template <typename T>
T& TMatrixContainer<T>::Get(const int Row, const int Column)
{
	check(IsValidIndex(Row, Column));
	return Matrix[Row][Column];
}

template <typename T>
const T& TMatrixContainer<T>::Get(const int Row, const int Column) const
{
	return Get(Row, Column);
}

template <typename T>
T& TMatrixContainer<T>::operator()(const int Row, const int Column)
{
	return Get(Row, Column);
}

template <typename T>
const T& TMatrixContainer<T>::operator()(const int Row, const int Column) const
{
	return Get(Row, Column);
}
