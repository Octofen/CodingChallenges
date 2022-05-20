// Fill out your copyright notice in the Description page of Project Settings.


#include "StarfieldStar.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"

FStarfieldStar::FStarfieldStar(float width, float height, float minSize, float maxSize, int index)
{
	this->Width = width;
	this->Height = height;

	X = FMath::RandRange(0.f, width);
	Y = FMath::RandRange(0.f, height);
	Z = FMath::RandRange(0.f, width * 0.5f);

	this->MinSize = minSize;
	this->MaxSize = maxSize;
	this->Index = index;
}

void FStarfieldStar::Update(float speed, float deltaRatio)
{
	Z -= speed * deltaRatio;

	if(Z < 1.f)
	{
		X = FMath::RandRange(0.f, Width);
		Y = FMath::RandRange(0.f, Height);
		Z = Width * 0.5f;
	}
}

FTransform FStarfieldStar::Show()
{
	FVector sv = UCCUtils::GetLocationFromCoordinates(X, Y, Width, Height);
	float sx = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-Width * 0.5f, Width * 0.5f), sv.Y / Z);
	float sy = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-Height * 0.5f, Height * 0.5f), sv.Z / Z);
	float r = FMath::GetMappedRangeValueClamped(FVector2D(0.f, Width * 0.5f), FVector2D(MaxSize, MinSize), Z);

	FVector location = FVector(-100.f, sx, sy);
	FVector scale = FVector(r);
	
	return FTransform(FRotator::ZeroRotator, location, scale);
}
