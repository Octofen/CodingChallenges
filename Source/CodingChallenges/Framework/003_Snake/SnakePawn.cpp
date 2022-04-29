// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "CodingChallenges/Framework/MainPlayerController.h"
#include "CodingChallenges/Data/003_Snake/SnakeData.h"
#include "CodingChallenges/Framework/CCUtils.h"

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

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());
	HalfWidth = viewport.X * 0.5f;
	HalfHeight = viewport.Y * 0.5f;

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->DoOnceAxisUpEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveUp);
		mainPlayerController->DoOnceAxisRightEvent.AddUniqueDynamic(this, &ASnakePawn::OnMoveRight);
	}

	
	X = FMath::RoundToFloat(-HalfWidth);
	Y = FMath::RoundToFloat(HalfHeight);
	XSpeed = 1.f;
	YSpeed = 0.f;

	InstancedStaticMesh->AddInstance(FTransform());
	Show();
}

void ASnakePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ElapsedTime += DeltaSeconds * Data->GameSpeed;

	if(ElapsedTime >= 1.f)
	{
		ElapsedTime = 0.f;
		Update();
		Show();
	}
}

void ASnakePawn::Update()
{
	X += XSpeed * Data->TileSize;
	Y += YSpeed * Data->TileSize;

	X = FMath::Clamp(X, -HalfWidth, HalfWidth - Data->TileSize);
	Y = FMath::Clamp(Y, -HalfHeight + Data->TileSize, HalfHeight);
}

void ASnakePawn::Show()
{
	FVector location = FVector(0.f, X + Data->TileSize * 0.5f, Y - Data->TileSize * 0.5f);
	FVector scale = FVector(Data->TileSize * 0.01f);
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
