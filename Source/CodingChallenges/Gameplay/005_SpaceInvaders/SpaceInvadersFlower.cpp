// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersFlower.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Data/005_SpaceInvaders/SpaceInvadersData.h"

FSpaceInvadersFlower::FSpaceInvadersFlower(float x, float y, float width, float height, USpaceInvadersData* data)
{
	this->Width = width;
	this->Height = height;

	this->X = x;;
	this->Y = y;

	this->Data = data;
}

FTransform FSpaceInvadersFlower::Show()
{
	FVector location = UCCUtils::GetLocationFromCoordinates(X, Y, Width, Height);
	FVector scale = FVector(Data->FlowerScale);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
