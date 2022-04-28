// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "MainPlayerController.h"
#include "CCUtils.h"
#include "FadeManager.h"
#include "Kismet/GameplayStatics.h"

AMainGameMode::AMainGameMode()
{
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

	UCCUtils::GetFadeManager()->FadeOut();
}
