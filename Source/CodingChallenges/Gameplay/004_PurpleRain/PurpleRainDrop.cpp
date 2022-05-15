// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainDrop.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Data/MasterData.h"

FPurpleRainDrop::FPurpleRainDrop(float width, float height)
{
	this->Width = width;
	this->Height = height;

	X = FMath::RandRange(0.f, Width);
	Y = FMath::RandRange(-200.f, -100.f);
	YSpeed = FMath::RandRange(4.f, 10.f);
	Length = FMath::RandRange(10.f, 20.f);
}

void FPurpleRainDrop::Fall(float delta)
{
	Y += YSpeed * delta * UCCUtils::GetMasterData()->FrameRate;

	if(Y > Height)
	{
		Y = FMath::RandRange(-200.f, -100.f);
	}
}

FTransform FPurpleRainDrop::Show()
{
	FVector location = FVector(-100.f, X - Width * 0.5f, -Y + Height * 0.5f);
	FVector scale = FVector(0.01f, 0.01f, Length * 0.01f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
