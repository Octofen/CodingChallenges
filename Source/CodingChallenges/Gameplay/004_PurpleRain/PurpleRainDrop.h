// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PurpleRainDrop.generated.h"

USTRUCT()
struct FPurpleRainDrop
{
	GENERATED_USTRUCT_BODY();

protected:
	float X;
	float Y;
	float YSpeed;

	float Width;
	float Height;

public:
	FPurpleRainDrop() { }

	FPurpleRainDrop(float width, float height);

	void Fall(float delta);

	FTransform Show();
};