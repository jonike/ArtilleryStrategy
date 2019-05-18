// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Projectile.h"
#include "BaseProjectile.generated.h"

/**
 * \brief Base class for all projectiles
 */
UCLASS()
class ARTILLERYSTRATEGY_API ABaseProjectile : public AActor, public IProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

	void AddImpulse(float Value) override;

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

private:
	/**
	 * \brief The amount of health that will be taken from collided object
	 */
	UPROPERTY(Category = Projectile, EditAnywhere)
	float Damage = 50.f;

	/**
	 * \brief Visuals
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	int BouncesBeforeDeath = 4;

	/**
	 * \brief Deal damage to collided object
	 * \param HitComponent The component that was hit
	 * \param OtherActor Collided actor
	 * \param OtherComp Collided component of other actor
	 * \param NormalImpulse Normal impulse
	 * \param Hit Hit info
	 */
	UFUNCTION()
	void DealDamage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
