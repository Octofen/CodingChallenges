// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeFood.h"

FSnakeFood::FSnakeFood(int columns, int rows)
{
	this->Columns = columns;
	this->Rows = rows;
}

FVector2D FSnakeFood::PickLocation(TArray<FVector2D> availableSpots)
{
	int rand = FMath::RandRange(0, availableSpots.Num() - 1);
	Position = availableSpots[rand];
	
	return Position;
}
