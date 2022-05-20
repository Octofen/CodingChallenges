// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceInvadersShip.generated.h"

UCLASS()
class CODINGCHALLENGES_API ASpaceInvadersShip : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* Mesh;

public:
	ASpaceInvadersShip();
};
