// Fill out your copyright notice in the Description page of Project Settings.


#include "PurpleRainManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Data/004_PurpleRain/PurpleRainData.h"
#include "CodingChallenges/Data/MasterData.h"

APurpleRainManager::APurpleRainManager()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Drop"));
	RootComponent = InstancedStaticMesh;
}

void APurpleRainManager::BeginPlay()
{
	Super::BeginPlay();

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	FVector2D viewport = UCCUtils::GetCameraViewportSize(GetWorld());

	for(int i = 0; i < 500; i++)
	{
		TSharedPtr<FPurpleRainDrop> drop = TSharedPtr<FPurpleRainDrop>(new FPurpleRainDrop(viewport.X, viewport.Y, Data));
		InstancedStaticMesh->AddInstance(drop->Show(), true);
		Drops.Add(drop);
	}
}

void APurpleRainManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float deltaRatio = DeltaSeconds * UCCUtils::GetMasterData()->FrameRate;

	for(int i = 0; i < Drops.Num(); i++)
	{
		TSharedPtr<FPurpleRainDrop> drop = Drops[i];
		drop->Fall(deltaRatio);
		InstancedStaticMesh->UpdateInstanceTransform(i, drop->Show(), true);
	}

	InstancedStaticMesh->MarkRenderStateDirty();
}
