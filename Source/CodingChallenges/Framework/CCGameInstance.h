// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CCGameInstance.generated.h"

class UMasterData;
class UFadeManager;

UCLASS()
class CODINGCHALLENGES_API UCCGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	static UCCGameInstance* Instance;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "_Settings")
	TSoftObjectPtr<UMasterData> MasterDataSoft;

	UPROPERTY()
	UMasterData* MasterData;

	UPROPERTY()
	UFadeManager* FadeManager;

public:
	void Init() override;

	void BeginDestroy() override;

	UMasterData* GetMasterData();

	UFadeManager* GetFadeManager();
};
