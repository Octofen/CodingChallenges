// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersManager.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Framework/005_SpaceInvaders/SpaceInvadersShip.h"

ASpaceInvadersManager::ASpaceInvadersManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpaceInvadersManager::BeginPlay()
{
	Super::BeginPlay();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());
	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(ASpaceInvadersShip* ship = Cast<ASpaceInvadersShip>(pawn))
	{
		ship->Initialize(viewport.X, viewport.Y);
	}
}