// Fill out your copyright notice in the Description page of Project Settings.


#include "Star.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"

AStar::AStar()
{
	PrimaryActorTick.bCanEverTick = false;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	RootComponent = Body;
}

void AStar::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* viewTarget = playerController->GetViewTarget();
	UActorComponent* component = viewTarget->GetComponentByClass(UCameraComponent::StaticClass());

	if (UCameraComponent* camera = Cast<UCameraComponent>(component))
	{
		FMinimalViewInfo view;
		camera->GetCameraView(0.f, view);

		HalfWidth = view.OrthoWidth * 0.5f;
		HalfHeight = HalfWidth / view.AspectRatio;

		X = FMath::RandRange(-HalfWidth, HalfWidth);
		Y = FMath::RandRange(-HalfHeight, HalfHeight);
		Z = FMath::RandRange(0.f, HalfWidth);
	}
}

void AStar::InitializeValues(float minSize, float maxSize)
{
	this->MinSize = minSize;
	this->MaxSize = maxSize;
}

void AStar::Update(float speed)
{
	Z -= speed;

	if (Z < 1.f)
	{
		X = FMath::RandRange(-HalfWidth, HalfWidth);
		Y = FMath::RandRange(-HalfHeight, HalfHeight);
		Z = HalfWidth;
	}
}

void AStar::Show()
{
	float sx = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-HalfWidth, HalfWidth), X / Z);
	float sy = FMath::GetMappedRangeValueUnclamped(FVector2D(-1.f, 1.f), FVector2D(-HalfHeight, HalfHeight), Y / Z);
	float r = FMath::GetMappedRangeValueClamped(FVector2D(0.f, HalfWidth), FVector2D(MaxSize, MinSize), Z);

	SetActorLocation(FVector(0.f, sx, sy));
	SetActorScale3D(FVector(r));
}
