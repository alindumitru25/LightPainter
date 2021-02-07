// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingPicker.h"
#include "../../Save/PaintingSaveGameIndex.h"
#include "PaintingButtons.h"
#include "Math/UnrealMathUtility.h"
#include "PaintingGrid.h"

// Sets default values
APaintingPicker::APaintingPicker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	PaintingGrid = CreateDefaultSubobject<UWidgetComponent>(TEXT("PaintingGrid"));
	PaintingGrid->SetupAttachment(GetRootComponent());

	ActionBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ActionBar"));
	ActionBar->SetupAttachment(GetRootComponent());
}

void APaintingPicker::AddPainting()
{
	UE_LOG(LogTemp, Warning, TEXT("THis is working"));
	UPainterSaveGame* NewPaint = UPainterSaveGame::Create();

	if (!NewPaint) return;

	NewPaint->Save();
	Populate();
}

void APaintingPicker::ToggleDeleteMode()
{
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());
	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearPaintings();
}

// Called when the game starts or when spawned
void APaintingPicker::BeginPlay()
{
	Super::BeginPlay();

	UPaintingButtons* PaintingButtons = Cast<UPaintingButtons>(ActionBar->GetUserWidgetObject());

	if (PaintingButtons)
	{
		PaintingButtons->SetParentPicker(this);
	}

	Populate();
}

int32 APaintingPicker::GetNumberOfPages() const
{
	UPaintingSaveGameIndex* SaveGameIndex = UPaintingSaveGameIndex::Load();
	TArray<FString> SlotNames = SaveGameIndex->GetSlotNames();
	float TotalSlots = (float)SlotNames.Num();

	if (!TotalSlots)
	{
		return 1;
	}

	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());

	if (!PaintingGridWidget) return 0;

	float PerPageSlots = (float)PaintingGridWidget->GetNumberOfSlots();

	return FMath::CeilToInt(TotalSlots / PerPageSlots);
}

void APaintingPicker::PopulateDots()
{
	int32 Pages = GetNumberOfPages();

	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());

	if (!PaintingGridWidget) return;

	PaintingGridWidget->ClearDots();

	if (Pages)
	{
		for (int32 i = 0; i < Pages; i++)
		{
			PaintingGridWidget->AddPaginationDot(i == CurrentPage);
		}
	}
}

void APaintingPicker::UpdateCurrentPage(int32 Offset)
{
	CurrentPage = FMath::Clamp(CurrentPage + Offset, 0, GetNumberOfPages() - 1);
	Populate();
}

void APaintingPicker::PopulateGrid()
{

	if (!PaintingGrid) return;
	UPaintingGrid* PaintingGridWidget = Cast<UPaintingGrid>(PaintingGrid->GetUserWidgetObject());

	if (!PaintingGridWidget) return;


	PaintingGridWidget->ClearPaintings();

	UPaintingSaveGameIndex* SaveGameIndex = UPaintingSaveGameIndex::Load();
	TArray<FString> SlotNames = SaveGameIndex->GetSlotNames();

	if (SlotNames.Num() && PaintingGrid != nullptr)
	{
		int32 SlotsNr = PaintingGridWidget->GetNumberOfSlots();
		int32 StartOffset = CurrentPage * SlotsNr;
		int32 EndOffset = StartOffset + SlotsNr;
		int32 Index = 0;

		for (int32 i = StartOffset; i < EndOffset && i < SlotNames.Num(); i++)
		{
			PaintingGridWidget->AddPainting(Index, SlotNames[i]);
			Index++;
		}
	}
}
