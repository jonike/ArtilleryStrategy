// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridPlatform.h"
#include "GridGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARTILLERYSTRATEGY_API UGridGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGridGenerator();

	UPROPERTY(EditAnywhere, Category = Generation)
		int Rows = 10;
	UPROPERTY(EditAnywhere, Category = Generation)
		int Columns = 10;
	UPROPERTY(EditAnywhere, Category = Generation)
		float Distance = 100.;
	UPROPERTY(EditAnywhere, Category = Generation)
		TSubclassOf<IGridPlatform> GridPlatormClass;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GenerateGrid();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};
