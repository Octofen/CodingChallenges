// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeFood.generated.h"

USTRUCT()
struct FSnakeFood
{
	GENERATED_USTRUCT_BODY()

public:
	FVector2D Position;

protected:
	int Columns;
	int Rows;

public:
	FSnakeFood() { };

	FSnakeFood(int columns, int rows);

	FVector2D PickLocation();
};