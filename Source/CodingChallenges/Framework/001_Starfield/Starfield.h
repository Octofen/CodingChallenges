// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CodingChallenges/Framework/MainGameMode.h"
#include "Starfield.generated.h"

class AStar;
class UStarfieldData;

UCLASS()
class CODINGCHALLENGES_API AStarfield : public AMainGameMode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|Starfield")
	TSoftObjectPtr<UStarfieldData> DataSoft;

	UPROPERTY()
	UStarfieldData* Data;

	UPROPERTY()
	TArray<AStar*> Stars;

public:
	AStarfield();

	void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;
};
