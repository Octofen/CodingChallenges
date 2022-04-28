// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Star.generated.h"

class UStarfieldData;

UCLASS()
class CODINGCHALLENGES_API AStar : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* Body;

	float X;
	float Y;
	float Z;

	float HalfWidth;
	float HalfHeight;

	float MinSize;
	float MaxSize;

public:	
	AStar();

	void BeginPlay() override;

	void InitializeValues(float minSize, float maxSize);

	void Update(float speed);

	void Show();
};
