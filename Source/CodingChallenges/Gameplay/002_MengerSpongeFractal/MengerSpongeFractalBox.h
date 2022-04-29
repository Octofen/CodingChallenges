// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MengerSpongeFractalBox.generated.h"

USTRUCT()
struct FMengerSpongeFractalBox
{
	GENERATED_USTRUCT_BODY()

protected:
	FVector Position;
	float Size;
	float BoundsSize;

public:
	FMengerSpongeFractalBox() { }

	FMengerSpongeFractalBox(float x, float y, float z, float size, float boundsSize);

	FTransform Show();

	TArray<TSharedPtr<FMengerSpongeFractalBox>> Generate();
};
