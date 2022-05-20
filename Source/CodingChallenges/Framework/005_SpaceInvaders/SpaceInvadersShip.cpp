// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersShip.h"
#include "CodingChallenges/Framework/CCUtils.h"

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

	X = width * 0.5f;

	float y = height - (GetActorScale().Y * 50.f);
	FVector location = UCCUtils::GetLocationFromCoordinates(X, y, width, height);
	SetActorLocation(location);
}
