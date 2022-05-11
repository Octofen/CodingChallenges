// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainDrop.h"

FPurpleRainDrop::FPurpleRainDrop(float width, float height)
{
	this->Width = width;
	this->Height = height;

	X = FMath::RandRange(0.f, Width);
	Y = FMath::RandRange(-200.f, -100.f);
	YSpeed = 1.f;
}

void FPurpleRainDrop::Fall()
{
	Y += YSpeed;
}

FTransform FPurpleRainDrop::Show()
{
	FVector location = FVector(-100.f, X - Width * 0.5f, -Y + Height * 0.5f);
	FVector scale = FVector(0.01f, 0.01f, 0.1f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
