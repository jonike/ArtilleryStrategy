// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InstancedMeshSpawner.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
UCLASS()
class ARTILLERYSTRATEGY_API AInstancedMeshSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInstancedMeshSpawner();

	auto GetTileInstancedMesh() const { return TileInstancedMesh; }

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(Category = "Tiles", EditAnywhere)
	UHierarchicalInstancedStaticMeshComponent* TileInstancedMesh;
};
