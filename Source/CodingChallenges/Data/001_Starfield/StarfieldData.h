// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StarfieldData.generated.h"

UCLASS()
class CODINGCHALLENGES_API UStarfieldData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	int NbStars = 100;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float MinStarSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float MaxStarSpeed = 6.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float MinStarSize = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float MaxStarSize = 1.f;
};
