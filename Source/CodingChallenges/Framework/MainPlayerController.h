// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMainControllerAxisEvent, int, value);

class UPauseMenu;
class UMasterData;

UCLASS()
class CODINGCHALLENGES_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	FMainControllerAxisEvent DoOnceAxisUpEvent;
	FMainControllerAxisEvent DoOnceAxisRightEvent;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	bool bMouseCursorAlwaysVisible = false;

	UPROPERTY()
	UPauseMenu* PauseMenu;

	bool bPauseMenuClassLoading = false;
	bool bAxisUpInputsActive = true;
	bool bAxisRightInputsActive = true;

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
	void OnAxisUp(float value);

	UFUNCTION()
	void OnAxisRight(float value);

	UFUNCTION()
	void OnMenuUp(int value);

	UFUNCTION()
	void OnMenuValidate();
};
