// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.h"
#include "PaintingSaveGameIndex.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingSaveGameIndex : public USaveGame
{
	GENERATED_BODY()

public:
	static UPaintingSaveGameIndex* Load();

	bool Save();

	void AddSaveGame(UPainterSaveGame* SaveGame);

	TArray<FString> GetSlotNames() const;

private:
	UPROPERTY()
	TArray<FString> SlotNames;
};
