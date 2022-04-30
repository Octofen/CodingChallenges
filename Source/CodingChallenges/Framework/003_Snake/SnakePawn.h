// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

class UCameraComponent;

UCLASS()
class CODINGCHALLENGES_API ASnakePawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

	FVector2D Position;
	FVector2D Speed;

	float HalfWidth;
	float HalfHeight;
	float TileSize;

public:
	ASnakePawn();

	void Initialize(float halfWidth, float halfHeight, float tileSize);

	void Update();

	FTransform Show();

protected:

	void Move(float x, float y);

	UFUNCTION()
	void OnMoveUp(float value);

	UFUNCTION()
	void OnMoveRight(float value);
};
