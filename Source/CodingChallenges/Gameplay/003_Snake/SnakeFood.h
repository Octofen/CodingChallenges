// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeFood.generated.h"

USTRUCT()
struct FSnakeFood
{
	GENERATED_USTRUCT_BODY()

protected:
	int Columns;
	int Rows;

public:
	FSnakeFood() { };

	FSnakeFood(int columns, int rows);

	FVector2D PickLocation();
};