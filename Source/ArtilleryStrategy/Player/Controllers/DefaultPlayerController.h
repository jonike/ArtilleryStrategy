// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CanBuyTiles.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyBuildings.h"
#include "Interfaces/FireManager.h"
#include "Interfaces/NeedsBuyWidget.h"
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
class ARTILLERYSTRATEGY_API ADefaultPlayerController : public APlayerController, public ICanBuyTiles, public IOwnerController, public ICanBuyBuildings, public IFireManager, public INeedsBuyWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingCreatedSignature, TScriptInterface<IBuilding>, CreatedBuilding);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileBoughtSignature, TScriptInterface<IGridPlatform>, Tile);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFireSignature);

public:
	ADefaultPlayerController();

	FOnBuildingCreatedSignature OnBuildingCreated;
	FOnTileBoughtSignature OnTileBought;
	FOnFireSignature OnFire;

	void BuyTile(TScriptInterface<IPlayerProperty> Cell) override;
	void HideBuyWidget() override;
	void ShowBuyWidget(TScriptInterface<IPlayerProperty> PropertyToBuy) override;
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
	UPROPERTY(Category = "Looking", EditAnywhere)
	float MinZoomDistance = 0.f;
	UPROPERTY(Category = "Looking", EditAnywhere)
	float MaxZoomDistance = 1600.f;
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

	bool TryToBuyWithPack(const FResourcePack& ResourcePack) const;
	bool TryToBuyDefaultBuilding(const TSubclassOf<AActor> BuildingClass) const;
	ADefaultHUD& GetDefaultHUD() const;
};
