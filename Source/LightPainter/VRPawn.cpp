// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "UI/PaintingPicker/PaintingPicker.h"
#include "EngineUtils.h"
#include "VRGameModeBase.h"

// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (RightControllerBPClass)
	{
		RightController = GetWorld()->SpawnActor<AHandControllerBase>(RightControllerBPClass);
		if (RightController != nullptr)
		{
			RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
			RightController->UpdateTrackingSource(EControllerHand::Right);
			RightController->SetOwner(this);
		}
	}

	if (LeftControllerBPClass)
	{
		LeftController = GetWorld()->SpawnActor<AHandControllerBase>(LeftControllerBPClass);
		if (LeftController != nullptr)
		{
			LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::SnapToTargetIncludingScale);
			LeftController->UpdateTrackingSource(EControllerHand::Left);
			LeftController->SetOwner(this);
		}
	}
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::HandleTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::HandleTriggerReleased);

	PlayerInputComponent->BindAxis(TEXT("PaginateRight"), this, &AVRPawn::PaginateRightAxisInput);
}

void AVRPawn::PaginateRightAxisInput(float AxisValue)
{
	int32 PaginationOffset = 0;
	PaginationOffset += AxisValue > PaginationThreshold ? 1 : 0;
	PaginationOffset += AxisValue < -PaginationThreshold ? -1 : 0;

	if (PaginationOffset != LastPaginationOffset && PaginationOffset != 0)
	{
		UpdateCurrentPage(PaginationOffset);
	}

	LastPaginationOffset = PaginationOffset;
}

void AVRPawn::UpdateCurrentPage(int32 Offset)
{
	for (TActorIterator<APaintingPicker> PaintingPickerItr(GetWorld()); PaintingPickerItr; ++PaintingPickerItr)
	{
		PaintingPickerItr->UpdateCurrentPage(Offset);
	}
}
