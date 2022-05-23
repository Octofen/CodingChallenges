// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpaceInvadersData.generated.h"

UCLASS()
class CODINGCHALLENGES_API USpaceInvadersData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Ship")
	FVector ShipScale = FVector(0.2f, 0.2f, 0.6f);

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Ship")
	float ShipSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Flowers")
	float FlowerScale = 0.6f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Flowers")
	int NbFlowers = 6;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Flowers")
	float FlowerSpacing = 80.f;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Flowers")
	float FlowerSpawnHeight = 340.f;
};
