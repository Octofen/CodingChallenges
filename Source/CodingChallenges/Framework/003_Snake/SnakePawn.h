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
	TArray<FVector2D> AvailableSpots;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

	FVector2D Speed;
	FVector2D TailPosition;

	int Columns;
	int Rows;

	bool bCheat = false;

public:
	ASnakePawn();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void Initialize(int columns, int rows);

	void Update();

	bool Eat(FVector2D foodPosition);

	bool Death();

	bool Cheat();

	bool Win();

protected:

	void Move(int x, int y);

	void Reset();

	UFUNCTION()
	void OnAddSnakePart();

	UFUNCTION()
	void OnMoveUp(int value);

	UFUNCTION()
	void OnMoveRight(int value);
};
