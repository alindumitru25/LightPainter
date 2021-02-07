// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingSaveGameIndex.h"
#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"

static const FString SlotName = "SaveGameIndex";

UPaintingSaveGameIndex* UPaintingSaveGameIndex::Load()
{
	UPaintingSaveGameIndex* SavedGame = Cast<UPaintingSaveGameIndex>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

	if (!SavedGame)
	{
		SavedGame = Cast<UPaintingSaveGameIndex>(UGameplayStatics::CreateSaveGameObject(UPaintingSaveGameIndex::StaticClass()));
	}

	return SavedGame;
}

bool UPaintingSaveGameIndex::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

void UPaintingSaveGameIndex::AddSaveGame(UPainterSaveGame* SaveGame)
{
	SlotNames.Add(SaveGame->GetSlotName());
}

TArray<FString> UPaintingSaveGameIndex::GetSlotNames() const
{
	return SlotNames;
}
