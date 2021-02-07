// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingCard.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPaintingCard::SetPaintingName(FString Name)
{
	if (SlotName != nullptr)
	{
		PaintingName = Name;
		FText SlotText = FText::FromString(Name);
		SlotName->SetText(SlotText);

		CardButton->OnClicked.AddDynamic(this, &UPaintingCard::CardButtonClicked);
	}
}

void UPaintingCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Map1"), true, "SlotName=" + PaintingName);
}
