// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SnakeData.generated.h"

UCLASS()
class CODINGCHALLENGES_API USnakeData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float TileSize = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float GameSpeed = 10.f;
};
