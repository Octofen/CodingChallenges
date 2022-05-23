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

	for(int i = 0; i < 6; i++)
	{
		float x = i * 80.f + 80.f;
		float y = 60.f;
		TSharedPtr<FSpaceInvadersFlower> flower = TSharedPtr<FSpaceInvadersFlower>(new FSpaceInvadersFlower(x, y, viewport.X, viewport.Y));
		Flowers.Add(flower);
		FlowerMesh->AddInstance(flower->Show(), true);
	}
}

void ASpaceInvadersManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for(int i = 0; i < Flowers.Num(); i++)
	{
		TSharedPtr<FSpaceInvadersFlower> flower = Flowers[i];
		FlowerMesh->UpdateInstanceTransform(i, flower->Show(), true);
	}

	FlowerMesh->MarkRenderStateDirty();
}
