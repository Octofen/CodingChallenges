// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StarfieldStar.generated.h"

class UCameraComponent;

USTRUCT()
struct FStarfieldStar
{
	GENERATED_USTRUCT_BODY()

public:
	int Index;

protected:
	float X;
	float Y;
	float Z;

	float Width;
	float Height;

	float MinSize;
	float MaxSize;

public:
	FStarfieldStar() { }

	FStarfieldStar(float width, float height, float minSize, float maxSize, int index);

	void Update(float speed, float deltaRatio);

	FTransform Show();
};