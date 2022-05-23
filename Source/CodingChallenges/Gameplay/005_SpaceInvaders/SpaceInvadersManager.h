// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceInvadersFlower.h"
#include "SpaceInvadersManager.generated.h"

class UInstancedStaticMeshComponent;

UCLASS()
class CODINGCHALLENGES_API ASpaceInvadersManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* FlowerMesh;

	TArray<TSharedPtr<FSpaceInvadersFlower>> Flowers;

public:	
	ASpaceInvadersManager();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
};
