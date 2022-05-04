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

void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Menu Validate", IE_Pressed, this, &ASnakePawn::OnAddSnakePart);
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

	Reset();
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

bool ASnakePawn::Death()
{
	FVector2D head = PartsPosition[0];

	for(int i = 1; i < PartsPosition.Num(); i++)
	{
		FVector2D pos = PartsPosition[i];
		int dist = FVector2D::DistSquared(head, pos);

		if(dist < 1)
		{
			Reset();
			return true;
		}
	}

	return false;
}

bool ASnakePawn::Cheat()
{
	if(bCheat)
	{
		bCheat = false;
		PartsPosition.Add(TailPosition);
		return true;
	}

	return false;
}

void ASnakePawn::Move(int x, int y)
{
	Speed = FVector2D(x, y);
}

void ASnakePawn::Reset()
{
	PartsPosition.Empty();

	PartsPosition.Add(FVector2D(0, 0));
	Speed = FVector2D(1, 0);
	TailPosition = PartsPosition[0];
}

void ASnakePawn::OnAddSnakePart()
{
	bCheat = true;
}

void ASnakePawn::OnMoveUp(float value)
{
	int i = value > 0.f ? -1 : 1;

	if(PartsPosition.Num() > 1 && Speed.Y + i == 0)
	{
		return;
	}

	Move(0, i);
}

void ASnakePawn::OnMoveRight(float value)
{
	int i = value > 0.f ? 1 : -1;

	if(PartsPosition.Num() > 1 && Speed.X + i == 0)
	{
		return;
	}

	Move(i, 0);
}
