// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "PaintingCard.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingCard : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPaintingName(FString Name);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UTextBlock* SlotName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* CardButton;

private:
	UFUNCTION()
	void CardButtonClicked();

	// State
	FString PaintingName;
};
