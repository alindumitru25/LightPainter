// Fill out your copyright notice in the Description page of Project Settings.


#include "HandControllerBase.h"
#include "MotionControllerComponent.h"

// Sets default values
AHandControllerBase::AHandControllerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VRHandRoot = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("VRHandRoot"));
	SetRootComponent(VRHandRoot);
	VRHandRoot->SetShowDeviceModel(true);

}

// Called when the game starts or when spawned
void AHandControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHandControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHandControllerBase::UpdateTrackingSource(const EControllerHand CurrentHand)
{
	VRHandRoot->SetTrackingSource(CurrentHand);
}

