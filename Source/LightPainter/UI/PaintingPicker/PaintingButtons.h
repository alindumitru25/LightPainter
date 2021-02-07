// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "PaintingPicker.h"
#include "PaintingButtons.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingButtons : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;

	void SetParentPicker(APaintingPicker* Picker) { ParentPicker = Picker; }

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* Add;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* Delete;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UButton* Load;

private:
	UFUNCTION()
	void OnLoad();

	UFUNCTION()
	void OnAdd();

	UFUNCTION()
	void OnDelete();

	UPROPERTY()
	APaintingPicker* ParentPicker;
};
