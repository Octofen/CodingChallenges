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

	PartsPosition.Add(FVector2D(0, 0));
	Speed = FVector2D(1, 0);
	TailPosition = PartsPosition[0];
}

void ASnakePawn::Update()
{
	TailPosition = PartsPosition.Last();

	for(int i = PartsPosition.Num() - 1; i > 0; i--)
	{
		PartsPosition[i] = PartsPosition[i - 1];
	}

	float x = PartsPosition[0].X + Speed.X;
	float y = PartsPosition[0].Y + Speed.Y;
	x = FMath::Clamp(x, 0, Columns - 1);
	y = FMath::Clamp(y, 0, Rows - 1);

	PartsPosition[0] = FVector2D(x, y);
}

bool ASnakePawn::Eat(FVector2D foodPosition)
{
	int dist = FVector2D::DistSquared(PartsPosition[0], foodPosition);
	
	if(dist < 1)
	{
		PartsPosition.Add(TailPosition);
		return true;
	}

	return false;
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
