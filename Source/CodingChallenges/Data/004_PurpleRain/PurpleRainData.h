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
	float DropMinAcceleration = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Speed")
	float DropMaxAcceleration = 0.2f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Scale")
	float DropMinLength = 10.f;

	UPROPERTY(EditDefaultsOnly,  Category = "_Settings\|Scale")
	float DropMaxLength = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Scale")
	float DropMinTickness = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Scale")
	float DropMaxTickness = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Depth")
	float DropMinDepth = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Depth")
	float DropMaxDepth = 20.f;
};
