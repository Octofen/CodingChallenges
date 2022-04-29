// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CCBlueprintLibrary.generated.h"

class UMasterData;
class UFadeManager;

UCLASS()
class CODINGCHALLENGES_API UCCBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UMasterData* GetMasterData();

	UFUNCTION(BlueprintPure)
	static UFadeManager* GetFadeManager();

	UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Abs %"))
	static int AbsoluteModulo(int value, int modulo);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "worldContext"))
	static FVector2D GetCameraViewportSize(UObject* worldContext);
};
