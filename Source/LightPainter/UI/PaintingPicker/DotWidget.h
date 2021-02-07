// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "DotWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UDotWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UImage* DotImage;

public:
	void SetActive(bool Active);
};
