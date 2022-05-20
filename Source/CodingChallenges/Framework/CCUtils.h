// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CCUtils.generated.h"

class UMasterData;
class UFadeManager;

UCLASS()
class CODINGCHALLENGES_API UCCUtils : public UObject
{
	GENERATED_BODY()
	
public:
	static UMasterData* GetMasterData();

	static UFadeManager* GetFadeManager();

	static int AbsoluteModulo(int value, int modulo);

	static FVector2D GetCameraViewportSize(UWorld* world);

	static FVector GetLocationFromCoordinates(float x, float y, float width, float height);
};
