// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceInvadersManager.generated.h"

UCLASS()
class CODINGCHALLENGES_API ASpaceInvadersManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpaceInvadersManager();

	virtual void BeginPlay() override;
};
