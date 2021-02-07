// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTouchingComponent.h"

void UWidgetTouchingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool isOver = IsOverInteractableWidget();

	if (isOver && !bInteracting)
	{
		bInteracting = true;
		PressPointerKey(EKeys::LeftMouseButton);
		UE_LOG(LogTemp, Warning, TEXT("Pressed"));
	}
	else if (!isOver && bInteracting)
	{
		bInteracting = false;
		ReleasePointerKey(EKeys::LeftMouseButton);
		UE_LOG(LogTemp, Warning, TEXT("Released"));
	}
}
