// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Data/MasterData.h"
#include "CodingChallenges/Framework/FadeManager.h"
#include "CodingChallenges/Framework/MainPlayerController.h"

void UPauseMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ButtonIndex = 0;
	HoverCurrentButton();
}

void UPauseMenu::MenuNavvigation(float value)
{
	ButtonIndex += value > 0.f ? 1 : -1;
	ButtonIndex = UCCUtils::AbsoluteModulo(ButtonIndex, 2);
	HoverCurrentButton();
}

void UPauseMenu::MenuValidate()
{
	ButtonIndex == 0 ? Resume() : Quit();
}

void UPauseMenu::Resume()
{
	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if(AMainPlayerController* mainPlayerController = Cast<AMainPlayerController>(playerController))
	{
		mainPlayerController->SetInputModeGameOnly();
		mainPlayerController->ChangeMouseCursorVisibility(false);
	}
}

void UPauseMenu::Quit()
{
	UWorld* world = GetWorld();
	APlayerController* playerController = world->GetFirstPlayerController();

	if (world->GetMapName().Contains("000_HUB"))
	{
		UKismetSystemLibrary::QuitGame(world, playerController, EQuitPreference::Quit, false);
	}
	else
	{
		UCCUtils::GetFadeManager()->OnFadeIn.AddUniqueDynamic(this, &UPauseMenu::OnChangeLevel);
		UCCUtils::GetFadeManager()->FadeIn();
	}
}

void UPauseMenu::OnChangeLevel()
{
	UCCUtils::GetFadeManager()->OnFadeIn.RemoveDynamic(this, &UPauseMenu::OnChangeLevel);

	UWorld* world = GetWorld();
	APlayerController* playerController = UGameplayStatics::GetPlayerController(world, 0);

	FInputModeGameOnly inputMode;
	playerController->SetInputMode(inputMode);
	playerController->bShowMouseCursor = false;

	FName levelName = FName(UCCUtils::GetMasterData()->HUBLevel.GetAssetName());
	UGameplayStatics::OpenLevel(world, levelName);
}
