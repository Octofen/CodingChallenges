// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HUBCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CODINGCHALLENGES_API AHUBCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	float TurnRateGamepad;

public:
	AHUBCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Move(float value, FVector axis);

	void MoveForward(float value);

	void MoveRight(float value);

	void TurnAtRate(float rate);

	void LookUpAtRate(float rate);
};
