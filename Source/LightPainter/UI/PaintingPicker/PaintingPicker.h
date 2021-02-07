// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "PaintingPicker.generated.h"

UCLASS()
class LIGHTPAINTER_API APaintingPicker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APaintingPicker();

	void AddPainting();

	void ToggleDeleteMode();

	void UpdateCurrentPage(int32 Offset);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Components
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* PaintingGrid;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ActionBar;

	int32 GetNumberOfPages() const;

	// State
	bool bIsDeleteMode = false;

	UPROPERTY(EditAnywhere)
	int32 CurrentPage = 0;

	// Utils
	void Populate() {
		PopulateDots();
		PopulateGrid();
	};

	void PopulateDots();

	void PopulateGrid();
};
