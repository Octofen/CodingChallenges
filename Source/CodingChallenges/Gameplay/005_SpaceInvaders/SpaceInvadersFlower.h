// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceInvadersFlower.generated.h"

class USpaceInvadersData;

USTRUCT()
struct FSpaceInvadersFlower
{
	GENERATED_USTRUCT_BODY();

protected:
	float X;
	float Y;

	float Width;
	float Height;

	UPROPERTY()
	USpaceInvadersData* Data;

public:
	FSpaceInvadersFlower() { };

	FSpaceInvadersFlower(float x, float y, float width, float height, USpaceInvadersData* data);

	FTransform Show();
};