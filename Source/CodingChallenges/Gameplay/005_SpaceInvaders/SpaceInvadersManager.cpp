// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersManager.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Framework/005_SpaceInvaders/SpaceInvadersShip.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CodingChallenges/Data/005_SpaceInvaders/SpaceInvadersData.h"

ASpaceInvadersManager::ASpaceInvadersManager()
{
	PrimaryActorTick.bCanEverTick = true;

	FlowerMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Flower"));
	RootComponent = FlowerMesh;
}

void ASpaceInvadersManager::BeginPlay()
{
	Super::BeginPlay();

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());
	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(ASpaceInvadersShip* ship = Cast<ASpaceInvadersShip>(pawn))
	{
		ship->Initialize(viewport.X, viewport.Y, Data);
	}

	float spacing = FMath::Max(Data->FlowerScale * 100.f, Data->FlowerSpacing);
	float y = FMath::Max(viewport.Y - Data->FlowerSpawnHeight, Data->FlowerScale * 50.f);

	for(int i = 0; i < Data->NbFlowers; i++)
	{
		float x = i * spacing + spacing;

		if(x > viewport.X - Data->FlowerScale * 50.f)
		{
			break;
		}

		TSharedPtr<FSpaceInvadersFlower> flower = TSharedPtr<FSpaceInvadersFlower>(new FSpaceInvadersFlower(x, y, viewport.X, viewport.Y, Data));
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
