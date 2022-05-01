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

public:
	TArray<FVector2D> PartsPosition;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

	FVector2D Speed;
	FVector2D TailPosition;

	int Columns;
	int Rows;

public:
	ASnakePawn();

	void Initialize(int columns, int rows);

	void Update();

	bool Eat(FVector2D foodPosition);

protected:

	void Move(int x, int y);

	UFUNCTION()
	void OnMoveUp(float value);

	UFUNCTION()
	void OnMoveRight(float value);
};
