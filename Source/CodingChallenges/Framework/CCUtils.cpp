// Fill out your copyright notice in the Description page of Project Settings.


#include "CCUtils.h"
#include "Kismet/GameplayStatics.h"
#include "CCGameInstance.h"
#include "CodingChallenges/Data/MasterData.h"
#include "FadeManager.h"
#include "Camera/CameraComponent.h"

UMasterData* UCCUtils::GetMasterData()
{
	return UCCGameInstance::Instance->GetMasterData();
}

UFadeManager* UCCUtils::GetFadeManager()
{
	return UCCGameInstance::Instance->GetFadeManager();
}

int UCCUtils::AbsoluteModulo(int value, int modulo)
{
	return (value % modulo + modulo) % modulo;
}

FVector2D UCCUtils::GetCameraViewportSize(UWorld* world)
{
	APlayerController* playerController = world->GetFirstPlayerController();
	AActor* viewTarget = playerController->GetViewTarget();
	UActorComponent* component = viewTarget->GetComponentByClass(UCameraComponent::StaticClass());
	UCameraComponent* camera = Cast<UCameraComponent>(component);

	FMinimalViewInfo view;
	camera->GetCameraView(0.f, view);

	ensureMsgf(view.ProjectionMode == ECameraProjectionMode::Orthographic, TEXT("UCCUtils::GetCameraViewportSize : Camera projection mode is not othographic"));

	if(view.ProjectionMode != ECameraProjectionMode::Orthographic)
	{
		return FVector2D();
	}

	return FVector2D(view.OrthoWidth, view.OrthoWidth * view.AspectRatio);
}
