// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeFood.h"

FSnakeFood::FSnakeFood(int columns, int rows)
{
	this->Columns = columns;
	this->Rows = rows;
}

FVector2D FSnakeFood::PickLocation()
{
	int x = FMath::RandRange(0, Columns - 1);
	int y = FMath::RandRange(0, Rows - 1);
	Position = FVector2D(x, y);
	
	return Position;
}
