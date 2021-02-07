// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
AStroke::AStroke()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	InstancedMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedMesh"));
	InstancedMesh->SetupAttachment(Root);

	JointMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("JointMesh"));
	JointMesh->SetupAttachment(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	StateLocations.Add(CursorLocation);

	if (PreviousCursorLocation.IsNearlyZero())
	{
		PreviousCursorLocation = CursorLocation;
		JointMesh->AddInstance(GetJointTransform(CursorLocation));
		return;
	}

	InstancedMesh->AddInstance(GetNextSegmentTransform(CursorLocation));
	JointMesh->AddInstance(GetJointTransform(CursorLocation));

	PreviousCursorLocation = CursorLocation;
}

FTransform AStroke::GetNextSegmentTransform(FVector CurrentLocation) const
{
	FTransform SegmentTransform;

	SegmentTransform.SetScale3D(GetNextSegmentScale(CurrentLocation));
	SegmentTransform.SetLocation(GetNextSegmentLocation(CurrentLocation));
	SegmentTransform.SetRotation(GetNextSegmentRotation(CurrentLocation));

	return SegmentTransform;
}

FVector AStroke::GetNextSegmentScale(FVector CurrentLocation) const
{
	// Subtract the vectors to get the distance.
	float Distance = (CurrentLocation - PreviousCursorLocation).Size();

	// we are only interest in scaling on X axis (since it gets spawned on X).
	return FVector(Distance, 1.f, 1.f);
}

FQuat AStroke::GetNextSegmentRotation(FVector CurrentLocation) const
{
	// Subtract to get the distance from CurrentLocation to PreviousLocation
	FVector Segment = CurrentLocation - PreviousCursorLocation;

	// Use forward vector (how the object is spawned) and Segment normal to find the angle in 3D (quat).
	return FQuat::FindBetweenNormals(CurrentLocation.ForwardVector, Segment.GetSafeNormal());
}

FVector AStroke::GetNextSegmentLocation(FVector CurrentLocation) const
{
	// We need the Location in Local space so use the current actor transform to get it.
	return GetActorTransform().InverseTransformPosition(PreviousCursorLocation);
}

FTransform AStroke::GetJointTransform(FVector CurrentLocation) const
{
	FTransform JointTransform;
	JointTransform.SetLocation(GetTransform().InverseTransformPosition(CurrentLocation));

	return JointTransform;
}

// Serialization
FStrokeState AStroke::SerializeToStruct() const
{
	FStrokeState SerializedStruct;
	SerializedStruct.Class = GetClass();
	SerializedStruct.ControlPoints = StateLocations;

	return SerializedStruct;

}

AStroke* AStroke::DeserializeFromStruct(const FStrokeState& StrokeState, UWorld* World)
{
	AStroke* StrokeObject = World->SpawnActor<AStroke>(StrokeState.Class);
	
	if (StrokeState.ControlPoints.Num() > 0)
	{
		for (FVector Location : StrokeState.ControlPoints)
		{
			StrokeObject->Update(Location);
		}
	}

	return StrokeObject;
}

