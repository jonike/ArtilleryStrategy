// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldGenerator.generated.h"

class UTileMatrix;
class IGridPlatform;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARTILLERYSTRATEGY_API UGridGenerator : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGridGenerationStartSignature);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGridGenerationEndSignature, int, Rows, int, Columns);

public:
	// Sets default values for this component's properties
	UGridGenerator();

	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GenerateGrid() const;

	FOnGridGenerationStartSignature OnGridGenerationStart;
	FOnGridGenerationEndSignature OnGridGenerationEnd;

protected:
	// Called when the game starts
	void BeginPlay() override;

private:
	UPROPERTY(Category = "Tiles", VisibleAnywhere)
	UTileMatrix* Matrix;
};
