// Fill out your copyright notice in the Description page of Project Settings.


#include "CCGameInstance.h"
#include "CodingChallenges/Data/MasterData.h"
#include "FadeManager.h"

UCCGameInstance* UCCGameInstance::Instance = nullptr;

void UCCGameInstance::Init()
{
	Super::Init();
	Instance = this;

	// MASTER DATA
	if(MasterDataSoft.IsPending())
	{
		MasterDataSoft.LoadSynchronous();
	}

	MasterData = MasterDataSoft.Get();

	// FADE MANAGER
	if(MasterData->FadeManagerClass.IsPending())
	{
		MasterData->FadeManagerClass.LoadSynchronous();
	}

	FadeManager = CreateWidget<UFadeManager>(this, MasterData->FadeManagerClass.Get());
}

void UCCGameInstance::BeginDestroy()
{
	Instance = nullptr;
	Super::BeginDestroy();
}

UMasterData* UCCGameInstance::GetMasterData()
{
	return MasterData;
}

UFadeManager* UCCGameInstance::GetFadeManager()
{
	return FadeManager;
}
