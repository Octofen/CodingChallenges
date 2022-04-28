// Fill out your copyright notice in the Description page of Project Settings.


#include "HUBCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AHUBCharacter::AHUBCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	TurnRateGamepad = 50.f;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AHUBCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AHUBCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AHUBCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AHUBCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AHUBCharacter::LookUpAtRate);
}

void AHUBCharacter::Move(float value, FVector axis)
{
	if(IsValid(Controller) && value != 0.f)
	{
		FRotator rotation = Controller->GetControlRotation();
		FRotator yawRotation = FRotator(0.f, rotation.Yaw, 0.f);
		FVector direction = yawRotation.RotateVector(axis);
		AddMovementInput(direction, value);
	}
}

void AHUBCharacter::MoveForward(float value)
{
	Move(value, FVector(1.f, 0.f, 0.f));
}

void AHUBCharacter::MoveRight(float value)
{
	Move(value, FVector(0.f, 1.f, 0.f));
}

void AHUBCharacter::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AHUBCharacter::LookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

