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
class UMaterialInterface;

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
	bool IsBuyWidgetVisible() const override;
	void ShowBuyWidget(ICanBeOwned& PropertyToBuy) override;
	USpringArmComponent* GetSpringArmComponent() const;

protected:
	void SetupInputComponent() override;

private:
	UPROPERTY(Category = Movement, EditAnywhere)
		float MaxMovementSpeed = 50.;
	UPROPERTY(Category = Looking, EditAnywhere)
		float ZoomRate = 200.;
	UPROPERTY(Category = Buying, EditDefaultsOnly)
		TSubclassOf<UUserWidget> BuyWidgetClass;
	UPROPERTY()
		UBuyPlatformWidget* BuyWidget = nullptr;
	UPROPERTY(Category = Color, EditAnywhere)
		UMaterialInterface* PlayerMaterial;

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
};
