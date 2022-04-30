// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeFood.generated.h"

USTRUCT()
struct FSnakeFood
{
	GENERATED_USTRUCT_BODY()

protected:
	FVector2D Position;

public:
	FSnakeFood() { };

	FSnakeFood(float halfWidth, float halfHeight, float tileSize);

	FTransform Show(float tileSize);
};