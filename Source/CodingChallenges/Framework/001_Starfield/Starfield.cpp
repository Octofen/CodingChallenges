// Fill out your copyright notice in the Description page of Project Settings.


#include "Starfield.h"
#include "CodingChallenges/Data/001_Starfield/StarfieldData.h"
#include "CodingChallenges/Gameplay/001_Starfield/Star/Star.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

AStarfield::AStarfield()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AStarfield::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();
}

void AStarfield::BeginPlay()
{
	Super::BeginPlay();

	if (Data->StarClass.IsPending())
	{
		Data->StarClass.LoadSynchronous();
	}

	for(int i = 0; i < Data->NbStars; i++)
	{
		FActorSpawnParameters param;
		param.Owner = this;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AStar* star = GetWorld()->SpawnActor<AStar>(Data->StarClass.Get(), FTransform(), param);
		star->InitializeValues(Data->MinStarSize, Data->MaxStarSize);
		Stars.Add(star);
	}
}

void AStarfield::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	float mousePositionX;
	float mousePositionY;
	playerController->GetMousePosition(mousePositionX, mousePositionY);

	int32 viewportX;
	int32 viewportY;
	playerController->GetViewportSize(viewportX, viewportY);

	float speed = FMath::GetMappedRangeValueClamped(FVector2D(0.f, (float) viewportX), FVector2D(Data->MinStarSpeed, Data->MaxStarSpeed), mousePositionX);

	for (AStar* star : Stars)
	{
		star->Update(speed);
		star->Show();
	}
}