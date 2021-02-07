// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 Index, FString PaintingName)
{
	if (!PaintingGrid) return;

	UPaintingCard* UserWidget = CreateWidget<UPaintingCard>(GetWorld(), GridCardClass);
	if (!UserWidget) return;

	UserWidget->SetPaintingName(PaintingName);

	USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(Index));
		
	if (SizeBox != nullptr)
	{
		SizeBox->AddChild(UserWidget);
	}
}

void UPaintingGrid::ClearPaintings()
{
	for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); i++)
	{
		USizeBox* SizeBox = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
		if (!SizeBox) continue;

		SizeBox->ClearChildren();
	}
}

void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!DotWidgetClass) return;

	UDotWidget* DotWidget = CreateWidget<UDotWidget>(GetWorld(), DotWidgetClass);
	if (!DotWidget) return;

	DotWidget->SetActive(Active);

	UHorizontalBoxSlot* BoxSlot = DotsContainer->AddChildToHorizontalBox(DotWidget);
	BoxSlot->SetPadding(FVector2D(8, 0));
}

void UPaintingGrid::ClearDots()
{
	if (!DotsContainer) return;

	DotsContainer->ClearChildren();
}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}
