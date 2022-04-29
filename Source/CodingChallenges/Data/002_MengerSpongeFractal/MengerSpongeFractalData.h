// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MengerSpongeFractalData.generated.h"

UCLASS()
class CODINGCHALLENGES_API UMengerSpongeFractalData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float RotationSpeed = 1.f;
};
