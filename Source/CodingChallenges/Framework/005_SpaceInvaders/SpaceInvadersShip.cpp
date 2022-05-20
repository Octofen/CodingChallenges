// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersShip.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/MainPlayerController.h"

ASpaceInvadersShip::ASpaceInvadersShip()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void ASpaceInvadersShip::Initialize(float width, float height)
{
	this->Width = width;
	this->Height = height;

	FVector scale = FVector(0.2f, 0.2f, 0.6f);
	X = width * 0.5f;
	Y = height - (scale.Z * 50.f);

	FVector location = UCCUtils::GetLocationFromCoordinates(X, Y, width, height);
	SetActorLocation(location);
	SetActorScale3D(scale);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->DoOnceAxisRightEvent.AddUniqueDynamic(this, &ASpaceInvadersShip::OnMove);
	}
}

void ASpaceInvadersShip::OnMove(int value)
{
	X += value * 5.f;

	FVector location = UCCUtils::GetLocationFromCoordinates(X, Y, Width, Height);
	SetActorLocation(location);
}
