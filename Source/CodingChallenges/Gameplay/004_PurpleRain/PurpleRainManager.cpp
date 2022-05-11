// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CodingChallenges/Framework/CCUtils.h"

APurpleRainManager::APurpleRainManager()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Drop"));
	RootComponent = InstancedStaticMesh;
}

void APurpleRainManager::BeginPlay()
{
	Super::BeginPlay();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());

	for(int i = 0; i < 100; i++)
	{
		TSharedPtr<FPurpleRainDrop> drop = TSharedPtr<FPurpleRainDrop>(new FPurpleRainDrop(viewport.X, viewport.Y));
		InstancedStaticMesh->AddInstance(drop->Show(), true);
		Drops.Add(drop);
	}
}

void APurpleRainManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for(int i = 0; i < Drops.Num(); i++)
	{
		TSharedPtr<FPurpleRainDrop> drop = Drops[i];
		drop->Fall(DeltaSeconds);
		InstancedStaticMesh->UpdateInstanceTransform(i, drop->Show(), true);
	}

	InstancedStaticMesh->MarkRenderStateDirty();
}
