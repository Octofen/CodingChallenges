// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainDrop.h"
#include "CodingChallenges/Data/004_PurpleRain/PurpleRainData.h"

FPurpleRainDrop::FPurpleRainDrop(float width, float height, UPurpleRainData* data)
{
	this->Width = width;
	this->Height = height;
	this->Data = data;

	ProcessLifetime();
}

void FPurpleRainDrop::Fall(float deltaRatio)
{
	Y += YSpeed * deltaRatio;

	if(Y > 0.f)
	{
		YSpeed += Acceleration * deltaRatio;
	}

	if(Y > Height)
	{
		ProcessLifetime();
	}
}

FTransform FPurpleRainDrop::Show()
{
	FVector location = FVector(-100.f, X - Width * 0.5f, -Y + Height * 0.5f);
	FVector scale = FVector(Tickness, Tickness, Length) * 0.01f;

	return FTransform(FRotator::ZeroRotator, location, scale);
}

void FPurpleRainDrop::ProcessLifetime()
{
	FVector2D depthRange = FVector2D(Data->DropMinDepth, Data->DropMaxDepth);
	FVector2D speedRange = FVector2D(Data->DropMinBaseSpeed, Data->DropMaxBaseSpeed);
	FVector2D lengthRange = FVector2D(Data->DropMinLength, Data->DropMaxLength);
	FVector2D ticknessRange = FVector2D(Data->DropMinTickness, Data->DropMaxTickness);
	FVector2D accelerationRange = FVector2D(Data->DropMinAcceleration, Data->DropMaxAcceleration);

	X = FMath::RandRange(0.f, Width);
	Y = FMath::RandRange(Data->DropHigherSpawnPosition * -1.f, Data->DropLowerSpawnPosition * -1.f);
	Z = FMath::RandRange(depthRange.X, depthRange.Y);
	YSpeed = FMath::GetMappedRangeValueClamped(depthRange, speedRange, Z);
	Length = FMath::GetMappedRangeValueClamped(depthRange, lengthRange, Z);
	Tickness = FMath::GetMappedRangeValueClamped(depthRange, ticknessRange, Z);
	Acceleration = FMath::GetMappedRangeValueClamped(depthRange, accelerationRange, Z);
}
