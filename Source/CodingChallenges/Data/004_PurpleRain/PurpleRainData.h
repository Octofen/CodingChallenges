// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PurpleRainData.generated.h"

UCLASS()
class CODINGCHALLENGES_API UPurpleRainData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Spawn")
	float DropLowerSpawnPosition = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Spawn")
	float DropHigherSpawnPosition = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Speed")
	float DropMinBaseSpeed = 4.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Speed")
	float DropMaxBaseSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Speed")
	float DropAcceleration = 0.05f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Length")
	float DropMinLength = 10.f;

	UPROPERTY(EditDefaultsOnly,  Category = "_Settings\|Length")
	float DropMaxLength = 20.f;
};
