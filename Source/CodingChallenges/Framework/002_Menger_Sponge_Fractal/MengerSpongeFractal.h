// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodingChallenges/Framework/MainGameMode.h"
#include "MengerSpongeFractal.generated.h"

class UMengerSpongeFractalData;
class AMengerSpongeFractalBox;

UCLASS()
class CODINGCHALLENGES_API AMengerSpongeFractal : public AMainGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<UMengerSpongeFractalData> DataSoft;

	UPROPERTY()
	UMengerSpongeFractalData* Data;

	UPROPERTY()
	TArray<AMengerSpongeFractalBox*> Sponge;

	FRotator randomRotation;
	int CurrentIteration = 0;

public:
	AMengerSpongeFractal();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	void Generate();

protected:
	void Refresh();
};
