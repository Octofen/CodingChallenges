// Fill out your copyright notice in the Description page of Project Settings.


#include "StarfieldStar.h"
#include "Kismet/GameplayStatics.h"

FStarfieldStar::FStarfieldStar(float halfWidth, float halfHeight, float minSize, float maxSize, int index)
{
	this->HalfWidth = halfWidth;
	this->HalfHeight = halfHeight;

	this->X = FMath::RandRange(-HalfWidth, HalfWidth);
	this->Y = FMath::RandRange(-HalfHeight, HalfHeight);
	this->Z = FMath::RandRange(0.f, HalfWidth);

	this->MinSize = minSize;
	this->MaxSize = maxSize;
	this->Index = index;
}

void FStarfieldStar::Update(float speed)
{
	this->Z -= speed;

	if(Z < 1.f)
	{
		this->X = FMath::RandRange(-HalfWidth, HalfWidth);
		this->Y = FMath::RandRange(-HalfHeight, HalfHeight);
		this->Z = HalfWidth;
	}
}

FTransform FStarfieldStar::Show()
{
	float sx = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-HalfWidth, HalfWidth), X / Z);
	float sy = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-HalfHeight, HalfHeight), Y / Z);
	float r = FMath::GetMappedRangeValueClamped(FVector2D(0.f, HalfWidth), FVector2D(MaxSize, MinSize), Z);

	FVector location = FVector(0.f, sx, sy);
	FVector scale = FVector(r);
	
	return FTransform(FRotator::ZeroRotator, location, scale);
}
