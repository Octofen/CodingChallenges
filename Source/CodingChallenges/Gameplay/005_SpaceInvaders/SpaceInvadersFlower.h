// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceInvadersFlower.generated.h"

USTRUCT()
struct FSpaceInvadersFlower
{
	GENERATED_USTRUCT_BODY();

protected:
	float X;
	float Y;

	float Width;
	float Height;

public:
	FSpaceInvadersFlower() { };

	FSpaceInvadersFlower(float width, float height);

	FTransform Show();
};