// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PainterSaveGame.generated.h"

USTRUCT()
struct FStrokeState
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<class AStroke> Class;

	UPROPERTY()
	TArray<FVector> ControlPoints;
};

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPainterSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	static UPainterSaveGame* Create();
	
	bool Save();

	static UPainterSaveGame* Load(FString SlotName);

	FString getState() const;

	void SerializeFromWorld(UWorld* World);

	void DeserializeToWorld(UWorld* World);

	FString GetSlotName() const {
		return SlotName;
	};

	void SetSlotName(FString NewSlotName) {
		SlotName = NewSlotName;
	};

private:
	UPROPERTY()
	FString GameState = TEXT("Game State");

	UPROPERTY()
	FString SlotName;

	UPROPERTY()
	TArray<FStrokeState> Strokes;

	// Util Functions
	void ClearWorld(UWorld* World);
};
