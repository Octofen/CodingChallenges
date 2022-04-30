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

void ASnakePawn::Initialize(float halfWidth, float halfHeight, float tileSize)
{
	this->HalfWidth = halfWidth;
	this->HalfHeight = halfHeight;
	this->TileSize = tileSize;

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->DoOnceAxisUpEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveUp);
		mainPlayerController->DoOnceAxisRightEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveRight);
	}

	float x = FMath::RoundToFloat(-HalfWidth);
	float y = FMath::RoundToFloat(HalfHeight);
	Position = FVector2D(x, y);
	Speed = FVector2D(1.f, 0.f);
}

void ASnakePawn::Update()
{
	Position.X += Speed.X * TileSize;
	Position.Y += Speed.Y * TileSize;

	Position.X = FMath::Clamp(Position.X, -HalfWidth, HalfWidth - TileSize);
	Position.Y = FMath::Clamp(Position.Y, -HalfHeight + TileSize, HalfHeight);
}

FTransform ASnakePawn::Show()
{
	float newX = Position.X;
	float newY = Position.Y;
	FVector newPos = FVector(0.f, newX, newY);
	FVector newScale = FVector(TileSize * 0.01f);

	return FTransform(FRotator::ZeroRotator, newPos, newScale);
}

void ASnakePawn::Move(float x, float y)
{
	Speed = FVector2D(x, y);
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
