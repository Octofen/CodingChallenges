// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UPauseMenu;
class UMasterData;

UCLASS()
class CODINGCHALLENGES_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	bool bMouseCursorAlwaysVisible = false;

	UPROPERTY()
	UPauseMenu* PauseMenu;

	bool bPauseMenuClassLoading = false;
	bool bMenuInputsActive = true;

public:
	void BeginPlay() override;

	void SetupInputComponent() override;
	
	void ChangeMouseCursorVisibility(bool bShow);

	void SetInputModeGameOnly();

	void SetInputModeGameAndUI(UUserWidget* widgetToFocus = nullptr, EMouseLockMode lockMode = EMouseLockMode::LockAlways);

protected:
	UFUNCTION()
	void OnPause();

	void OnPauseMenuClassLoaded(UMasterData* masterData);

	UFUNCTION()
	void OnMenuUp(float value);

	UFUNCTION()
	void OnMenuValidate();
};
