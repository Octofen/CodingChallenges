// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

class UInstancedStaticMeshComponent;
class UCameraComponent;
class USnakeData;

UCLASS()
class CODINGCHALLENGES_API ASnakePawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* InstancedStaticMesh;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<USnakeData> DataSoft;

	UPROPERTY()
	USnakeData* Data;

	float X;
	float Y;
	float XSpeed;
	float YSpeed;

	float HalfWidth;
	float HalfHeight;

	float ElapsedTime = 0.f;

public:
	ASnakePawn();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

protected:
	void Update();

	void Show();

	void Move(float x, float y);

	UFUNCTION()
	void OnMoveUp(float value);

	UFUNCTION()
	void OnMoveRight(float value);
};
