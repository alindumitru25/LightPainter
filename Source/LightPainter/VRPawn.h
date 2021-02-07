// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HandControllerBase.h"
#include "Save/PainterSaveGame.h"
#include "VRPawn.generated.h"

UCLASS()
class LIGHTPAINTER_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* VRRoot;

	UPROPERTY()
	AHandControllerBase* LeftController;

	UPROPERTY()
	AHandControllerBase* RightController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> LeftControllerBPClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AHandControllerBase> RightControllerBPClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationThreshold = 0.9;

	void HandleTriggerPressed() { if (RightController) RightController->HandleTriggerPressed(); }
	void HandleTriggerReleased() { if (RightController) RightController->HandleTriggerReleased(); }

	void PaginateRightAxisInput(float AxisValue);
	void UpdateCurrentPage(int32 Offset);

	// State
	int32 LastPaginationOffset = 0;
};
