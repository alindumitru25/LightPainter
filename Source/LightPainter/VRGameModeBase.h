// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VRGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API AVRGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

	UFUNCTION(BlueprintCallable)
	void Save();

	void Load();

protected:
	virtual void BeginPlay() override;

private:
	// State
	FString SlotName;
};
