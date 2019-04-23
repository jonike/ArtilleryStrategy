// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyBuildings.h"
#include "Interfaces/FireManager.h"
#include "DefaultPlayerController.generated.h"

class UUserWidget;
class USpringArmComponent;
class UBuyPlatformWidget;
class UBuildingSelectorWidget;
class UMaterialInterface;
class IWallet;
class ADefaultHUD;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerController : public APlayerController, public ICanBuyCells, public IOwnerController, public ICanBuyBuildings, public IFireManager
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingCreatedSignature, TScriptInterface<IBuilding>, CreatedBuilding);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSignature);

public:
	ADefaultPlayerController();

	FOnBuildingCreatedSignature OnBuildingCreated;
	FOnFireSignature OnFire;

	void BuyCell(TScriptInterface<ICanBeOwned> Cell) override;
	void HideBuyWidget() override;
	void ShowBuyWidget(TScriptInterface<ICanBeOwned> PropertyToBuy) override;
	bool IsBuyWidgetVisible() const override;

	UTexture2D* GetOwnerIcon() const override;
	UMaterialInterface* GetOwnerMaterial() const override;
	TScriptInterface<IWallet> GetWallet() const override;

	void CreateSelectedBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) override;

	void AddToFireList(TScriptInterface<IWeaponBuilding> Weapon) override;

	USpringArmComponent* GetSpringArmComponent() const;

protected:
	void SetupInputComponent() override;

private:
	UPROPERTY(Category = Movement, EditAnywhere)
	float MaxMovementSpeed = 50.;
	UPROPERTY(Category = Looking, EditAnywhere)
	float ZoomRate = 200.;
	UPROPERTY(Category = Property, EditAnywhere)
	UMaterialInterface* PlayerMaterial;
	UPROPERTY(Category = "Property", EditDefaultsOnly)
	UTexture2D* PlayerIcon;

	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void Zoom(float Value);
	UFUNCTION()
	void FireAllWeapon();

	bool TryToBuy(const FResourcePack& ResourcePack) const;

	AActor* SpawnBuildingActor(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) const;
	ADefaultHUD& GetDefaultHUD() const;
};
