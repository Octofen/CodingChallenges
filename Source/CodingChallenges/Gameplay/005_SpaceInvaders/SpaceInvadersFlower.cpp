// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersFlower.h"
#include "CodingChallenges/Framework/CCUtils.h"

FSpaceInvadersFlower::FSpaceInvadersFlower(float width, float height)
{
	this->Width = width;
	this->Height = height;

	X = width * 0.5f;
	Y = 50.f;
}

FTransform FSpaceInvadersFlower::Show()
{
	FVector location = UCCUtils::GetLocationFromCoordinates(X, Y, Width, Height);
	FVector scale = FVector(0.6f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
