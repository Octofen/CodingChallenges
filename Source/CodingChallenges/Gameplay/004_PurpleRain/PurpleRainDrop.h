// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PurpleRainDrop.generated.h"

class UPurpleRainData;

USTRUCT()
struct FPurpleRainDrop
{
	GENERATED_USTRUCT_BODY();

protected:
	float X;
	float Y;
	float Z;
	float YSpeed;
	float Length;
	float Tickness;
	float Acceleration;

	float Width;
	float Height;

	UPROPERTY()
	UPurpleRainData* Data;

public:
	FPurpleRainDrop() { }

	FPurpleRainDrop(float width, float height, UPurpleRainData* data);

	void Fall(float deltaRatio);

	FTransform Show();

protected:
	void ProcessLifetime();
};