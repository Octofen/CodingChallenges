// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersManager.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Framework/005_SpaceInvaders/SpaceInvadersShip.h"
#include "Components/InstancedStaticMeshComponent.h"

ASpaceInvadersManager::ASpaceInvadersManager()
{
	PrimaryActorTick.bCanEverTick = true;

	FlowerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Flower"));
	RootComponent = FlowerMesh;
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

	Flower = TSharedPtr<FSpaceInvadersFlower>(new FSpaceInvadersFlower(viewport.X, viewport.Y));
	FlowerMesh->AddInstance(Flower->Show(), true);
}

void ASpaceInvadersManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FlowerMesh->UpdateInstanceTransform(0, Flower->Show(), true, true);
}
