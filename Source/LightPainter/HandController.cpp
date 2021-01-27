// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"
#include "Stroke.h"
#include "MotionControllerComponent.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRHandRoot = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("VRHandRoot"));
	SetRootComponent(VRHandRoot);
	VRHandRoot->SetShowDeviceModel(true);
}

// Called when the game starts or when spawned
void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandController::UpdateTrackingSource(const EControllerHand CurrentHand)
{
	VRHandRoot->SetTrackingSource(CurrentHand);
}

void AHandController::HandleTriggerPressed()
{
	GetWorld()->SpawnActor<AStroke>(StrokeBPClass, GetActorLocation(), FRotator(0, 0, 0));
}

void AHandController::HandleTriggerReleased()
{
}

