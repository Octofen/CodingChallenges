// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFadeEvent);

UENUM()
enum class EFadeStep : uint8
{
	FS_NONE = 0,
	FS_IN = 1,
	FS_HOLD = 2,
	FS_OUT = 3
};

USTRUCT()
struct FFadeInfo
{
	GENERATED_USTRUCT_BODY()

public:
	bool bAutoFade = false;
	float Duration = 0.5f;
	float ScreenDuration = 1.f;
};

UCLASS()
class CODINGCHALLENGES_API UFadeManager : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FFadeEvent OnFadeIn;
	FFadeEvent OnFadeOut;

protected:
	FFadeInfo CurrentFadeInfo;
	FTimerHandle timerHandle;
	float NormalizedElapsed = 0.f;
	EFadeStep CurrentStep;

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	void FadeInOut(float duration = 0.5f, float screenDuration = 1.f, FLinearColor color = FLinearColor::Black);

	void FadeIn(float duration = 0.5f, FLinearColor color = FLinearColor::Black);

	void FadeOut(float duration = 0.5f, FLinearColor color = FLinearColor::Black);

protected:
	void Fade(FFadeInfo fadeInfo, EFadeStep startingStep, FLinearColor fadeColor);

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor(FLinearColor color);

	UFUNCTION(BlueprintImplementableEvent)
	void SetOpacity(float opacity);
};
