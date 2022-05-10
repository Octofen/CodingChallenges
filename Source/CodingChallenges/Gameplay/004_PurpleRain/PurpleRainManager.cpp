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
	Drop = TSharedPtr<FPurpleRainDrop>(new FPurpleRainDrop(viewport.X, viewport.Y));

	InstancedStaticMesh->AddInstance(Drop->Show(), true);
}

void APurpleRainManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Drop->Fall();
	InstancedStaticMesh->UpdateInstanceTransform(0, Drop->Show(), true, true);
}
