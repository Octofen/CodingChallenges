// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGame.h"
#include "CodingChallenges/Data/003_Snake/SnakeData.h"
#include "CodingChallenges/Framework/003_Snake/SnakePawn.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "Components/InstancedStaticMeshComponent.h"

ASnakeGame::ASnakeGame()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SnakePartsMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Snake Parts"));
	SnakePartsMesh->SetupAttachment(Root);

	FoodMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Food"));
	FoodMesh->SetupAttachment(Root);
}

void ASnakeGame::BeginPlay()
{
	Super::BeginPlay();

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());
	int columns = FMath::FloorToFloat(viewport.X / Data->TileSize);
	int rows = FMath::FloorToFloat(viewport.Y / Data->TileSize);
	HalfWidth = viewport.X * 0.5f;
	HalfHeight = viewport.Y * 0.5f;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Snake = Cast<ASnakePawn>(pawn);
	Snake->Initialize(columns, rows);
	FTransform snakeT = ConstructTransform(Snake->Position);
	SnakePartsMesh->AddInstance(snakeT);

	SnakeFood = TSharedPtr<FSnakeFood>(new FSnakeFood(columns, rows));
	FTransform foodT = ConstructTransform(SnakeFood->PickLocation());
	FoodMesh->AddInstance(foodT);
}

void ASnakeGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ElapsedTime += DeltaSeconds * Data->GameSpeed;

	if(ElapsedTime >= 1.f)
	{
		ElapsedTime = 0.f;
		Snake->Update();

		FTransform snakeT = ConstructTransform(Snake->Position);
		SnakePartsMesh->UpdateInstanceTransform(0, snakeT, false, true);
	}
}

FTransform ASnakeGame::ConstructTransform(FVector2D inPos)
{
	float x = (inPos.X * Data->TileSize) - HalfWidth + Data->TileSize * 0.5f;
	float y = (inPos.Y * Data->TileSize * -1) + HalfHeight - Data->TileSize * 0.5f;
	FVector location = FVector(0.f, x, y);
	FVector scale = FVector(Data->TileSize * 0.01f);

	return FTransform(FRotator::ZeroRotator, location, scale);
}
