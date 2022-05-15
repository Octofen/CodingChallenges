// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PurpleRainDrop.h"
#include "PurpleRainManager.generated.h"

class UInstancedStaticMeshComponent;
class UPurpleRainData;

UCLASS()
class CODINGCHALLENGES_API APurpleRainManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* InstancedStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<UPurpleRainData> DataSoft;

	UPROPERTY()
	UPurpleRainData* Data;

	TArray<TSharedPtr<FPurpleRainDrop>> Drops;

public:	
	APurpleRainManager();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
};
