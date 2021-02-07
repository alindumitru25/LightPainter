// Fill out your copyright notice in the Description page of Project Settings.


#include "DotWidget.h"

void UDotWidget::SetActive(bool Active)
{
	if (!DotImage) return;

	if (!Active)
	{
		DotImage->SetOpacity(0.5);
	}
}
