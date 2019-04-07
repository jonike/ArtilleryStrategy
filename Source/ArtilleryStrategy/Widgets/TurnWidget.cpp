// Fill out your copyright notice in the Description page of Project Settings.

#include "TurnWidget.h"
#include "Components/TurnProcessorComponent.h"

void UTurnWidget::EndTurn()
{
	const auto TurnProcessor = GetTurnProcessor(this);
	TurnProcessor->EndTurn();
}
