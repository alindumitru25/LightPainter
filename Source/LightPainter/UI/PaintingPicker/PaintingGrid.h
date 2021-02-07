// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingCard.h"
#include "DotWidget.h"
#include "Components/HorizontalBox.h"
#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddPainting(int32 Index, FString PaintingName);

	void ClearPaintings();

	void AddPaginationDot(bool Active);

	void ClearDots();

	int32 GetNumberOfSlots() const;
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* DotsContainer;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDotWidget> DotWidgetClass;
};
