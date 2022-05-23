// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersFlower.h"
#include "CodingChallenges/Framework/CCUtils.h"

FSpaceInvadersFlower::FSpaceInvadersFlower(float x, float y, float width, float height)
{
	this->Width = width;
	this->Height = height;

	this->X = x;;
	this->Y = y;
}

FTransform FSpaceInvadersFlower::Show()
{
	FVector location = UCCUtils::GetLocationFromCoordinates(X, Y, Width, Height);
	FVector scale = FVector(0.6f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
