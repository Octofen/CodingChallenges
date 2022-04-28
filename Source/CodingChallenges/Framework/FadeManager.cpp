// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeManager.h"
#include "Kismet/GameplayStatics.h"

void UFadeManager::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(CurrentStep == EFadeStep::FS_NONE)
	{
		return;
	}

	switch(CurrentStep)
	{
		case EFadeStep::FS_IN:
		{
			NormalizedElapsed += InDeltaTime / CurrentFadeInfo.Duration;
			float opacity = FMath::Clamp(NormalizedElapsed, 0.f, 1.f);
			SetOpacity(opacity);

			if(NormalizedElapsed >= 1.f)
			{
				NormalizedElapsed = 0.f;
				OnFadeIn.Broadcast();
				CurrentStep = CurrentFadeInfo.bAutoFade ? EFadeStep::FS_HOLD : EFadeStep::FS_NONE;
			}

			break;
		}

		case EFadeStep::FS_HOLD:
		{
			NormalizedElapsed += InDeltaTime / CurrentFadeInfo.ScreenDuration;

			if(NormalizedElapsed >= 1.f)
			{
				NormalizedElapsed = 0.f;
				CurrentStep = EFadeStep::FS_OUT;
			}

			break;
		}

		case EFadeStep::FS_OUT:
		{
			NormalizedElapsed += InDeltaTime / CurrentFadeInfo.Duration;
			float opacity = FMath::Clamp(1.f - NormalizedElapsed, 0.f, 1.f);
			SetOpacity(opacity);

			if(NormalizedElapsed >= 1.f)
			{
				NormalizedElapsed = 0.f;
				CurrentStep = EFadeStep::FS_NONE;
				OnFadeOut.Broadcast();

				RemoveFromParent();
			}

			break;
		}
	}
}

void UFadeManager::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	
}

void UFadeManager::FadeInOut(float duration, float screenDuration, FLinearColor color)
{
	FFadeInfo info;
	info.bAutoFade = true;
	info.Duration = duration;
	info.ScreenDuration = screenDuration;

	Fade(info, EFadeStep::FS_IN, color);
}

void UFadeManager::FadeIn(float duration, FLinearColor color)
{
	FFadeInfo info;
	info.bAutoFade = false;
	info.Duration = duration;

	Fade(info, EFadeStep::FS_IN, color);
}

void UFadeManager::FadeOut(float duration, FLinearColor color)
{
	FFadeInfo info;
	info.bAutoFade = false;
	info.Duration = duration;

	Fade(info, EFadeStep::FS_OUT, color);
}

void UFadeManager::Fade(FFadeInfo fadeInfo, EFadeStep startingStep, FLinearColor fadeColor)
{
	if(CurrentStep != EFadeStep::FS_NONE)
	{
		return;
	}

	CurrentFadeInfo = fadeInfo;
	NormalizedElapsed = 0.f;
	CurrentStep = startingStep;

	if(!IsInViewport())
	{
		AddToViewport(999999);
	}

	SetColor(fadeColor);
}
