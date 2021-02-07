// Fill out your copyright notice in the Description page of Project Settings.


#include "VRGameModeBase.h"
#include "Save/PainterSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void AVRGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
}

void AVRGameModeBase::Save()
{
	UE_LOG(LogTemp, Warning, TEXT("Saving..."));
	UPainterSaveGame* SaveGameObject = UPainterSaveGame::Load(SlotName);

	if (SaveGameObject)
	{
		SaveGameObject->SerializeFromWorld(GetWorld());
		SaveGameObject->Save();

		UStereoLayerFunctionLibrary::ShowSplashScreen();
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"), true);
	}
}

void AVRGameModeBase::Load()
{
	UPainterSaveGame* SavedSlotGame = UPainterSaveGame::Load(SlotName);

	if (SavedSlotGame)
	{
		SavedSlotGame->SetSlotName(SlotName);
		SavedSlotGame->DeserializeToWorld(GetWorld());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not load saved game..."));
	}
}

void AVRGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}


