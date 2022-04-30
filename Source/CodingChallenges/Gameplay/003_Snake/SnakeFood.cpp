// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeFood.h"

FSnakeFood::FSnakeFood(float halfWidth, float halfHeight, float tileSize)
{
	float foodX = FMath::RandRange(-halfWidth, halfWidth - tileSize);
	float foodY = FMath::RandRange(-halfHeight + tileSize, halfHeight);
	Position = FVector2D(foodX, foodY);
}

FTransform FSnakeFood::Show(float tileSize)
{
	FVector newFoodPos = FVector(0.f, Position.X, Position.Y);
	FVector newFoodScale = FVector(tileSize * 0.01f);

	return FTransform(FRotator::ZeroRotator, newFoodPos, newFoodScale);
}
