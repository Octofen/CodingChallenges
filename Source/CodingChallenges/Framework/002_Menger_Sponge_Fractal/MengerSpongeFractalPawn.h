// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MengerSpongeFractalPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CODINGCHALLENGES_API AMengerSpongeFractalPawn : public APawn
{
	GENERATED_BODY()

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
