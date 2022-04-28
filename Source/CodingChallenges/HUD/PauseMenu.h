// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

UCLASS()
class CODINGCHALLENGES_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	int ButtonIndex = 0;

public:
	void NativeOnInitialized() override;

	void MenuNavvigation(float value);

	void MenuValidate();

protected:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HoverCurrentButton();

	UFUNCTION(BlueprintCallable)
	void Resume();

	UFUNCTION(BlueprintCallable)
	void Quit();

	UFUNCTION()
	void OnChangeLevel();
};
