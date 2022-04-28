// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class CODINGCHALLENGES_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings\|General")
	bool bShowMouseCursor = false;

public:
	AMainGameMode();

	void BeginPlay() override;
};
