// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceInvadersShip.generated.h"

class USpaceInvadersData;

UCLASS()
class CODINGCHALLENGES_API ASpaceInvadersShip : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* Mesh;

	float X;
	float Y;

	float Width;
	float Height;

	UPROPERTY()
	USpaceInvadersData* Data;

public:
	ASpaceInvadersShip();

	void Initialize(float width, float height, USpaceInvadersData* data);

protected:
	UFUNCTION()
	void OnMove(int value);
};
