// Fill out your copyright notice in the Description page of Project Settings.
#include "PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"
#include "PaintingSaveGameIndex.h"
#include "../Stroke.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(UPainterSaveGame::StaticClass()));
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if (!NewSaveGame->Save()) return nullptr;

	UPaintingSaveGameIndex* SaveGameIndex = UPaintingSaveGameIndex::Load();
	SaveGameIndex->AddSaveGame(NewSaveGame);
	SaveGameIndex->Save();

	UE_LOG(LogTemp, Warning, TEXT("Created new save game."));

	TArray<FString> SlotNames = SaveGameIndex->GetSlotNames();
	for (FString SlotName : SlotNames)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *SlotName);
	}

	return NewSaveGame;

}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

FString UPainterSaveGame::getState() const
{
	return GameState;
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	Strokes.Empty();

	for (TActorIterator<AStroke> StrokeIt(World); StrokeIt; ++StrokeIt)
	{
		Strokes.Add(StrokeIt->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);

	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::DeserializeFromStruct(StrokeState, World);
	}
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeIt(World); StrokeIt; ++StrokeIt)
	{
		StrokeIt->Destroy();
	}
}
