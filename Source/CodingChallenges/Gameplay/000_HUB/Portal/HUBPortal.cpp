// Fill out your copyright notice in the Description page of Project Settings.


#include "HUBPortal.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/BlueprintPathsLibrary.h"
#include "CodingChallenges/Framework/000_HUB/HUBCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/CCUtils.h"
#include "CodingChallenges/Framework/FadeManager.h"
#include "Engine/LevelStreaming.h"

AHUBPortal::AHUBPortal()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Effect"));
	Effect->SetupAttachment(Root);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Effect);

	SignBoard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Signboard"));
	SignBoard->SetupAttachment(Root);

	LevelName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Level Name"));
	LevelName->SetupAttachment(SignBoard);
}

void AHUBPortal::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	Trigger->OnComponentBeginOverlap.RemoveAll(this);
	Trigger->OnComponentBeginOverlap.AddUniqueDynamic(this, &AHUBPortal::OnOverlap);
	 
	if(!Level.IsNull())
	{
		TArray<FString> strArray;
		FString name = UBlueprintPathsLibrary::GetBaseFilename(Level.ToString());
		name.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		name.ParseIntoArray(strArray, TEXT("_"));
		strArray.RemoveAt(0);

		FString result = FString::Join(strArray, TEXT(" "));
		LevelName->SetText(FText::FromString(result));
	}
}

void AHUBPortal::OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if(!Level.IsNull() && otherActor->IsA(AHUBCharacter::StaticClass()))
	{
		UCCUtils::GetFadeManager()->OnFadeIn.AddUniqueDynamic(this, &AHUBPortal::OnChangeLevel);
		UCCUtils::GetFadeManager()->FadeIn();
	}
}

void AHUBPortal::OnChangeLevel()
{
	UCCUtils::GetFadeManager()->OnFadeIn.RemoveDynamic(this, &AHUBPortal::OnChangeLevel);
	UGameplayStatics::OpenLevel(GetWorld(), FName(Level.GetAssetName()));
}
