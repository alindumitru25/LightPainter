// Copyright Epic Games, Inc. All Rights Reserved.


#include "LightPainterGameModeBase.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

void ALightPainterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UStereoLayerFunctionLibrary::HideSplashScreen();
}
