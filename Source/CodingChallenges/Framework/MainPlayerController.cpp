// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "CodingChallenges/HUD/PauseMenu.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "CCUtils.h"
#include "CodingChallenges/Data/MasterData.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = bMouseCursorAlwaysVisible;

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);

	if(bMouseCursorAlwaysVisible)
	{
		SetInputModeGameAndUI();
	}

	DoOnceAxisUpEvent.AddUniqueDynamic(this, &AMainPlayerController::OnMenuUp);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputActionBinding& pauseBinding = InputComponent->BindAction("Pause", IE_Pressed, this, &AMainPlayerController::OnPause);
	pauseBinding.bExecuteWhenPaused = true;
	pauseBinding.bConsumeInput = false;

	FInputAxisBinding& axisUpBinding = InputComponent->BindAxis("Menu Up / Down", this, &AMainPlayerController::OnAxisUp);
	axisUpBinding.bExecuteWhenPaused = true;
	axisUpBinding.bConsumeInput = false;

	FInputAxisBinding& axisRightBinding = InputComponent->BindAxis("Menu Right / Left", this, &AMainPlayerController::OnAxisRight);
	axisRightBinding.bExecuteWhenPaused = true;
	axisRightBinding.bConsumeInput = false;

	FInputActionBinding& menuValidateBinding = InputComponent->BindAction("Menu Validate", IE_Pressed, this, &AMainPlayerController::OnMenuValidate);
	menuValidateBinding.bExecuteWhenPaused = true;
	menuValidateBinding.bConsumeInput = false;
}

void AMainPlayerController::ChangeMouseCursorVisibility(bool bShow)
{
	if(bMouseCursorAlwaysVisible)
	{
		return;
	}

	bShowMouseCursor = bShow;
}

void AMainPlayerController::SetInputModeGameOnly()
{
	if(bMouseCursorAlwaysVisible)
	{
		SetInputModeGameAndUI();
		return;
	}

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);
}

void AMainPlayerController::SetInputModeGameAndUI(UUserWidget* widgetToFocus, EMouseLockMode lockMode)
{
	FInputModeGameAndUI inputMode;
	inputMode.SetLockMouseToViewportBehavior(lockMode);
	inputMode.SetHideCursorDuringCapture(false);

	if(IsValid(widgetToFocus))
	{
		inputMode.SetWidgetToFocus(widgetToFocus->TakeWidget());
	}

	SetInputMode(inputMode);
}

void AMainPlayerController::OnPause()
{
	if (!IsValid(PauseMenu))
	{
		if(bPauseMenuClassLoading)
		{
			return;
		}

		UMasterData* masterData = UCCUtils::GetMasterData();

		if (masterData->PauseMenuClass.IsPending())
		{
			bPauseMenuClassLoading = true;

			UAssetManager::GetStreamableManager().RequestAsyncLoad(
				masterData->PauseMenuClass.ToSoftObjectPath(),
				FStreamableDelegate::CreateUObject(this, &AMainPlayerController::OnPauseMenuClassLoaded, masterData));
		}
		else
		{
			OnPauseMenuClassLoaded(masterData);
		}
	}
	else
	{
		if (UGameplayStatics::IsGamePaused(GetWorld()))
		{
			PauseMenu->RemoveFromParent();
			UGameplayStatics::SetGamePaused(GetWorld(), false);

			SetInputModeGameOnly();
			ChangeMouseCursorVisibility(false);
		}
		else
		{
			PauseMenu->AddToViewport();
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			SetInputModeGameAndUI(PauseMenu, EMouseLockMode::DoNotLock);
			ChangeMouseCursorVisibility(true);
		}
	}
}

void AMainPlayerController::OnPauseMenuClassLoaded(UMasterData* masterData)
{
	bPauseMenuClassLoading = false;
	PauseMenu = CreateWidget<UPauseMenu>(this, masterData->PauseMenuClass.Get());
	OnPause();
}

void AMainPlayerController::OnAxisUp(float value)
{
	UMasterData* masterData = UCCUtils::GetMasterData();
	float abs = FMath::Abs(value);

	if(!bAxisUpInputsActive && abs < masterData->AxisResetValue)
	{
		bAxisUpInputsActive = true;
	}

	if(bAxisUpInputsActive && abs >= masterData->AxisDeadZone)
	{
		bAxisUpInputsActive = false;
		DoOnceAxisUpEvent.Broadcast(value);
	}
}

void AMainPlayerController::OnAxisRight(float value)
{
	UMasterData* masterData = UCCUtils::GetMasterData();
	float abs = FMath::Abs(value);

	if(!bAxisRightInputsActive && abs < masterData->AxisResetValue)
	{
		bAxisRightInputsActive = true;
	}

	if(bAxisRightInputsActive && abs >= masterData->AxisDeadZone)
	{
		bAxisRightInputsActive = false;
		DoOnceAxisRightEvent.Broadcast(value);
	}
}

void AMainPlayerController::OnMenuUp(float value)
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && IsValid(PauseMenu))
	{
		PauseMenu->MenuNavvigation(value);
	}
}

void AMainPlayerController::OnMenuValidate()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()) && IsValid(PauseMenu))
	{
		PauseMenu->MenuValidate();
	}
}
