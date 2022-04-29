// Fill out your copyright notice in the Description page of Project Settings.


#include "StarfieldManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "CodingChallenges/Data/001_Starfield/StarfieldData.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AStarfieldManager::AStarfieldManager()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Star Mesh"));
	RootComponent = InstancedStaticMesh;
}

void AStarfieldManager::BeginPlay()
{
	Super::BeginPlay();

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	AActor* viewTarget = playerController->GetViewTarget();
	UActorComponent* component = viewTarget->GetComponentByClass(UCameraComponent::StaticClass());

	if(UCameraComponent* camera = Cast<UCameraComponent>(component))
	{
		FMinimalViewInfo view;
		camera->GetCameraView(0.f, view);

		float halfWidth = view.OrthoWidth * 0.5f;
		float halfHeight = halfWidth / view.AspectRatio;

		for(int i = 0; i < Data->NbStars; i++)
		{
			int index = InstancedStaticMesh->AddInstance(FTransform(), true);

			TSharedPtr<FStarfieldStar> star(new FStarfieldStar(halfWidth, halfHeight, Data->MinStarSize, Data->MaxStarSize, index));
			Stars.Add(star);
		}
	}
}

void AStarfieldManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APlayerController* playerController = GetWorld()->GetFirstPlayerController();

	float mousePositionX;
	float mousePositionY;
	playerController->GetMousePosition(mousePositionX, mousePositionY);

	int32 viewportX;
	int32 viewportY;
	playerController->GetViewportSize(viewportX, viewportY);

	float speed = FMath::GetMappedRangeValueClamped(FVector2D(0.f, (float) viewportX), FVector2D(Data->MinStarSpeed, Data->MaxStarSpeed), mousePositionX);

	for(const TSharedPtr<FStarfieldStar>& star : Stars)
	{
		star->Update(speed);
		FTransform t = star->Show();

		InstancedStaticMesh->UpdateInstanceTransform(star->Index, t, true);
	}

	InstancedStaticMesh->MarkRenderStateDirty();
}
