// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Camera/CameraComponent.h"
#include "CodingChallenges/Framework/MainPlayerController.h"

ASnakePawn::ASnakePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

void ASnakePawn::Initialize(int columns, int rows)
{
	this->Columns = columns;
	this->Rows = rows;

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->DoOnceAxisUpEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveUp);
		mainPlayerController->DoOnceAxisRightEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveRight);
	}

	Position = FVector2D(0, 0);
	Speed = FVector2D(1, 0);
}

void ASnakePawn::Update()
{
	Position.X += Speed.X;
	Position.Y += Speed.Y;

	Position.X = FMath::Clamp(Position.X, 0, Columns - 1);
	Position.Y = FMath::Clamp(Position.Y, 0, Rows - 1);
}

bool ASnakePawn::Eat(FVector2D foodPosition)
{
	int dist = FVector2D::DistSquared(Position, foodPosition);
	return dist < 1;
}

void ASnakePawn::Move(int x, int y)
{
	Speed = FVector2D(x, y);
}

void ASnakePawn::OnMoveUp(float value)
{
	int i = value > 0.f ? -1 : 1;
	Move(0, i);
}

void ASnakePawn::OnMoveRight(float value)
{
	int i = value > 0.f ? 1 : -1;
	Move(i, 0);
}
