// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainDrop.h"
#include "CodingChallenges/Data/004_PurpleRain/PurpleRainData.h"

FPurpleRainDrop::FPurpleRainDrop(float width, float height, UPurpleRainData* data)
{
	this->Width = width;
	this->Height = height;
	this->Data = data;

	X = FMath::RandRange(0.f, Width);
	Y = FMath::RandRange(data->DropHigherSpawnPosition * -1.f, data->DropLowerSpawnPosition * -1.f);
	YSpeed = FMath::RandRange(data->DropMinBaseSpeed, data->DropMaxBaseSpeed);
	Length = FMath::RandRange(data->DropMinLength, data->DropMaxLength);
}

void FPurpleRainDrop::Fall(float deltaRatio)
{
	Y += YSpeed * deltaRatio;

	if(Y > 0.f)
	{
		YSpeed += Data->DropAcceleration * deltaRatio;
	}

	if(Y > Height)
	{
		Y = FMath::RandRange(Data->DropHigherSpawnPosition * -1.f, Data->DropLowerSpawnPosition * -1.f);
		YSpeed = FMath::RandRange(Data->DropMinBaseSpeed, Data->DropMaxBaseSpeed);
	}
}

FTransform FPurpleRainDrop::Show()
{
	FVector location = FVector(-100.f, X - Width * 0.5f, -Y + Height * 0.5f);
	FVector scale = FVector(0.01f, 0.01f, Length * 0.01f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
