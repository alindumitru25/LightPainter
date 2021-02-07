// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingButtons.h"

bool UPaintingButtons::Initialize()
{
	if (!Super::Initialize()) return false;

	Add->OnClicked.AddDynamic(this, &UPaintingButtons::OnAdd);
	Delete->OnClicked.AddDynamic(this, &UPaintingButtons::OnDelete);
	Load->OnClicked.AddDynamic(this, &UPaintingButtons::OnLoad);

	return true;
}

void UPaintingButtons::OnLoad()
{
	UE_LOG(LogTemp, Warning, TEXT("Load clicked"));
}

void UPaintingButtons::OnAdd()
{
	if (ParentPicker)
	{
		ParentPicker->AddPainting();
	}
}

void UPaintingButtons::OnDelete()
{
	if (ParentPicker)
	{
		ParentPicker->ToggleDeleteMode();
	}
}
