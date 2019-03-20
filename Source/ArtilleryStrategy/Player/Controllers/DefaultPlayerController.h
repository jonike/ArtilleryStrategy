// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/CanBuyCells.h"
#include "Interfaces/OwnerController.h"
#include "DefaultPlayerController.generated.h"

class UUserWidget;
class USpringArmComponent;
class UBuyPlatformWidget;
class UBuildingSelectorWidget;
class UMaterialInterface;
class IWallet;

/**
 *
 */
UCLASS()
class ARTILLERYSTRATEGY_API ADefaultPlayerController : public APlayerController, public ICanBuyCells, public IOwnerController
{
	GENERATED_BODY()

public:
	ADefaultPlayerController();

	void BuyCell(ICanBeOwned& Cell) override;
	void HideBuyWidget() override;
	void ShowBuyWidget(ICanBeOwned& PropertyToBuy) override;

	bool IsBuyWidgetVisible() const override;

	USpringArmComponent* GetSpringArmComponent() const;

protected:
	void SetupInputComponent() override;

private:
	UPROPERTY(Category = Movement, EditAnywhere)
		float MaxMovementSpeed = 50.;
	UPROPERTY(Category = Looking, EditAnywhere)
		float ZoomRate = 200.;

	// TODO: restrict widget selection to classes that implement specific interface
	UPROPERTY(Category = Widgets, EditDefaultsOnly)
		TSubclassOf<UUserWidget> BuyWidgetClass;
	UPROPERTY(Category = Widgets, EditDefaultsOnly)
		TSubclassOf<UUserWidget> BuildingsSelectorWidgetClass;


	UPROPERTY(Category = Widgets, EditAnywhere)
		bool bShouldAutoCloseBuyWidget = true;
	UPROPERTY(Category = Widgets, EditAnywhere)
		bool bShouldAutoCloseBuildingsWidget = true;
	UPROPERTY(Category = Property, EditAnywhere)
		UMaterialInterface* PlayerMaterial;

	// TODO: as only one widget can be shown at a time, remove unused widget and organize widget management
	UPROPERTY()
		UBuyPlatformWidget* BuyWidget = nullptr;
	UPROPERTY()
		UBuildingSelectorWidget* BuildingSelectorWidget = nullptr;

	UFUNCTION()
		void MoveForward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void Zoom(float Value);
	UFUNCTION()
		void WhenCloseClicked();
	UFUNCTION()
		void WhenBuyClicked(TScriptInterface<ICanBeOwned> Property);

	UMaterialInterface& GetOwnerMaterial() const override;

	IWallet& GetWallet() const;

	void CreateBuyWidget();
};
