// Fill out your copyright notice in the Description page of Project Settings.


#include "MengerSpongeFractalPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMengerSpongeFractalPawn::AMengerSpongeFractalPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	RootComponent = SpringArm;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AMengerSpongeFractalPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Menu Validate", IE_Pressed, this, &AMengerSpongeFractalPawn::OnGenerate);
	PlayerInputComponent->BindAction("Mouse Validate", IE_Pressed, this, &AMengerSpongeFractalPawn::OnGenerate);
}

void AMengerSpongeFractalPawn::OnGenerate()
{
	GenerateEvent.Broadcast();
}
