// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Save/PainterSaveGame.h"
#include "Stroke.generated.h"

UCLASS()
class LIGHTPAINTER_API AStroke : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStroke();

	void Update(FVector CursorLocation);

	FStrokeState SerializeToStruct() const;

	static AStroke* DeserializeFromStruct(const FStrokeState& StrokeState, UWorld* World);

private:

	FTransform GetNextSegmentTransform(FVector CurrentLocation) const;

	FVector GetNextSegmentScale(FVector CurrentLocation) const;

	FQuat GetNextSegmentRotation(FVector CurrentLocation) const;

	FVector GetNextSegmentLocation(FVector CurrentLocation) const;

	FTransform GetJointTransform(FVector CurrentLocation) const;

	// Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
		class UInstancedStaticMeshComponent* InstancedMesh;

	UPROPERTY(VisibleAnywhere)
		class UInstancedStaticMeshComponent* JointMesh;

	// State
	FVector PreviousCursorLocation;

	TArray<FVector> StateLocations;
};
