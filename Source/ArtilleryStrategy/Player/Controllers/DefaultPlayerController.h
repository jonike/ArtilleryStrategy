// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Interfaces/OwnerController.h"
#include "Interfaces/CanBuyBuildings.h"
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
class ARTILLERYSTRATEGY_API ADefaultPlayerController : public APlayerController, public ICanBuyCells, public IOwnerController, public ICanBuyBuildings
{
	GENERATED_BODY()

public:
	ADefaultPlayerController();

	void BuyCell(TScriptInterface<ICanBeOwned> Cell) override;
	void HideBuyWidget() override;
	void ShowBuyWidget(TScriptInterface<ICanBeOwned> PropertyToBuy) override;
	bool IsBuyWidgetVisible() const override;

	void BuyBuilding(TScriptInterface<IGridPlatform> Cell, TSubclassOf<AActor> BuildingClass) override;

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

	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void Zoom(float Value);

	UMaterialInterface& GetOwnerMaterial() const override;

	TScriptInterface<IWallet> GetWallet() const;
	ADefaultHUD& GetDefaultHUD() const;
};
