// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPointerHandController.h"
#include "MotionControllerComponent.h"
#include "Components/WidgetInteractionComponent.h"

AUIPointerHandController::AUIPointerHandController()
{
	InteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("InteractionComponent"));
	InteractionComponent->SetupAttachment(GetRootComponent());
	InteractionComponent->bShowDebug = true;
}

void AUIPointerHandController::HandleTriggerPressed()
{
	InteractionComponent->PressPointerKey(EKeys::LeftMouseButton);
}

void AUIPointerHandController::HandleTriggerReleased()
{
	InteractionComponent->ReleasePointerKey(EKeys::LeftMouseButton);
}
