// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MengerSpongeFractalPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMengerSpongeFractalPawnEvent);

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CODINGCHALLENGES_API AMengerSpongeFractalPawn : public APawn
{
	GENERATED_BODY()

public:
	FMengerSpongeFractalPawnEvent GenerateEvent;

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

public:
	AMengerSpongeFractalPawn();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnGenerate();
};
