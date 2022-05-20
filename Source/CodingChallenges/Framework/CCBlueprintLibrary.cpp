// Fill out your copyright notice in the Description page of Project Settings.


#include "CCBlueprintLibrary.h"
#include "CodingChallenges/Data/MasterData.h"
#include "CCUtils.h"
#include "FadeManager.h"

UMasterData* UCCBlueprintLibrary::GetMasterData()
{
	return UCCUtils::GetMasterData();
}

UFadeManager* UCCBlueprintLibrary::GetFadeManager()
{
	return UCCUtils::GetFadeManager();
}

int UCCBlueprintLibrary::AbsoluteModulo(int value, int modulo)
{
	return UCCUtils::AbsoluteModulo(value, modulo);
}

FVector2D UCCBlueprintLibrary::GetCameraViewportSize(UObject* worldContext)
{
	UWorld* world = GEngine->GetWorldFromContextObject(worldContext, EGetWorldErrorMode::ReturnNull);
	return UCCUtils::GetCameraViewportSize(world);
}

FVector UCCBlueprintLibrary::GetLocationFromCoordinates(float x, float y, float width, float height)
{
	return UCCUtils::GetLocationFromCoordinates(x, y, width, height);
}
