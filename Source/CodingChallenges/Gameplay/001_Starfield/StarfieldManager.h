// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StarfieldStar.h"
#include "StarfieldManager.generated.h"

class UInstancedStaticMeshComponent;
class UStarfieldData;

UCLASS()
class CODINGCHALLENGES_API AStarfieldManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* InstancedStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<UStarfieldData> DataSoft;

	UPROPERTY()
	UStarfieldData* Data;

	TArray<TSharedPtr<FStarfieldStar>> Stars;

public:	
	AStarfieldManager();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
};
