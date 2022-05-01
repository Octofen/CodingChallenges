// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeFood.h"
#include "SnakeGame.generated.h"

class USnakeData;
class ASnakePawn;
class UInstancedStaticMeshComponent;

UCLASS()
class CODINGCHALLENGES_API ASnakeGame : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* SnakePartsMesh;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* FoodMesh;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<USnakeData> DataSoft;

	UPROPERTY()
	USnakeData* Data;

	UPROPERTY()
	ASnakePawn* Snake;

	TSharedPtr<FSnakeFood> SnakeFood;

	float HalfWidth;
	float HalfHeight;
	float ElapsedTime = 0.f;

public:	
	ASnakeGame();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

protected:
	FTransform ConstructTransform(FVector2D inPos);
};
