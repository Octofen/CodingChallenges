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
	HalfWidth = viewport.X * 0.5f;
	HalfHeight = viewport.Y * 0.5f;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	Snake = Cast<ASnakePawn>(pawn);
	Snake->Initialize(HalfWidth, HalfHeight, Data->TileSize);
	FTransform snakeT = Snake->Show();
	SnakePartsMesh->AddInstance(AdjustLocation(snakeT));

	SnakeFood = TSharedPtr<FSnakeFood>(new FSnakeFood(HalfWidth, HalfHeight, Data->TileSize));
	FTransform foodT = SnakeFood->Show(Data->TileSize);
	FoodMesh->AddInstance(AdjustLocation(foodT));
}

void ASnakeGame::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ElapsedTime += DeltaSeconds * Data->GameSpeed;

	if(ElapsedTime >= 1.f)
	{
		ElapsedTime = 0.f;
		Snake->Update();

		FTransform snakeT = Snake->Show();
		SnakePartsMesh->UpdateInstanceTransform(0, AdjustLocation(snakeT), false, true);
	}
}

FTransform ASnakeGame::AdjustLocation(FTransform inT)
{
	float x = inT.GetLocation().Y + HalfWidth;
	float y = inT.GetLocation().Z + HalfHeight;
	float col = FMath::FloorToFloat(x / Data->TileSize);
	float row = FMath::FloorToFloat(y / Data->TileSize);
	float resultX = (col * Data->TileSize) - HalfWidth + Data->TileSize * 0.5f;
	float resultY = (row * Data->TileSize) - HalfHeight - Data->TileSize * 0.5f;

	inT.SetLocation(FVector(0.f, resultX, resultY));
	return inT;
}
