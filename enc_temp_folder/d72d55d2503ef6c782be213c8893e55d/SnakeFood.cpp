// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeFood.h"

FSnakeFood::FSnakeFood(int columns, int rows)
{
	this->Columns = columns;
	this->Rows = rows;
}

FVector2D FSnakeFood::PickLocation()
{
	float x = FMath::RandRange(0, Columns - 1);
	float y = FMath::RandRange(0, Rows - 1);
	return  FVector2D(Columns, Rows);
}
