// Fill out your copyright notice in the Description page of Project Settings.


#include "CCUtils.h"
#include "Kismet/GameplayStatics.h"
#include "CCGameInstance.h"
#include "CodingChallenges/Data/MasterData.h"
#include "FadeManager.h"

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
