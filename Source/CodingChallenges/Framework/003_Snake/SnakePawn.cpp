// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "CodingChallenges/Framework/MainPlayerController.h"

ASnakePawn::ASnakePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Snake Parts"));
	RootComponent = InstancedStaticMesh;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->DoOnceAxisUpEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveUp);
		mainPlayerController->DoOnceAxisRightEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveRight);
	}

	X = 0.f;
	Y = 0.f;
	XSpeed = 1.f;
	YSpeed = 0.f;

	InstancedStaticMesh->AddInstance(FTransform());
	Show();
}

void ASnakePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Update();
	Show();
}

void ASnakePawn::Update()
{
	X += XSpeed;
	Y += YSpeed;
}

void ASnakePawn::Show()
{
	FVector location = FVector(0.f, X, Y);
	FVector scale = FVector(0.1f);
	FTransform t = FTransform(FRotator::ZeroRotator, location, scale);

	InstancedStaticMesh->UpdateInstanceTransform(0, t, false, true);
}

void ASnakePawn::Move(float x, float y)
{
	XSpeed = x;
	YSpeed = y;
}

void ASnakePawn::OnMoveUp(float value)
{
	value = value > 0.f ? 1.f : -1.f;
	Move(0.f, value);
}

void ASnakePawn::OnMoveRight(float value)
{
	value = value > 0.f ? 1.f : -1.f;
	Move(value, 0.f);
}
