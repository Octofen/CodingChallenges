// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MasterData.generated.h"

class UPauseMenu;
class UFadeManager;

UCLASS()
class CODINGCHALLENGES_API UMasterData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Pause")
	TSoftClassPtr<UPauseMenu> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Pause")
	TSoftObjectPtr<UWorld> HUBLevel;

	// The input will allow the axis update only above that value
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Controller")
	float AxisDeadZone = 0.3f;

	// After a successfull axis update
	// The input will allow another axis update only if it's reset bellow that value
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Controller")
	float AxisResetValue = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Fade")
	TSoftClassPtr<UFadeManager> FadeManagerClass;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Frame Rate")
	float FrameRate = 60.f;
};
