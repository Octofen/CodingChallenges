// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MengerSpongeFractalBox.h"
#include "MengerSpongeFractalManager.generated.h"

class UInstancedStaticMeshComponent;
class UMengerSpongeFractalData;

UCLASS()
class CODINGCHALLENGES_API AMengerSpongeFractalManager : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UInstancedStaticMeshComponent* InstancedStaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<UMengerSpongeFractalData> DataSoft;

	UPROPERTY()
	UMengerSpongeFractalData* Data;

	int NbIterations = 0;
	FVector Bounds;
	FRotator RandomRotation;
	TArray<TSharedPtr<FMengerSpongeFractalBox>> Sponge;

public:	
	AMengerSpongeFractalManager();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

protected:
	void Refresh();

	UFUNCTION()
	void OnGenerate();
};
