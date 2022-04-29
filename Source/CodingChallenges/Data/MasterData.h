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

	// The input will allow the navigation in the menu only above that value
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Pause")
	float AxisDeadZone = 0.3f;

	// After a successfull menu navigation
	// The input will allow another navigation in the menu only if it's reset bellow that value
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Pause")
	float AxisResetValue = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Fade")
	TSoftClassPtr<UFadeManager> FadeManagerClass;
};
