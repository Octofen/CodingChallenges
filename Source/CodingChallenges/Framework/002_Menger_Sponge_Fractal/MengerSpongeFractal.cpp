// Fill out your copyright notice in the Description page of Project Settings.


#include "MengerSpongeFractal.h"
#include "CodingChallenges/Data/002_MengerSpongeFractal/MengerSpongeFractalData.h"
#include "Engine/AssetManager.h"
#include "CodingChallenges/Gameplay/002_MengerSpongeFractal/MengerSpongeFractalBox.h"
#include "Kismet/GameplayStatics.h"

AMengerSpongeFractal::AMengerSpongeFractal()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AMengerSpongeFractal::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();
}

void AMengerSpongeFractal::BeginPlay()
{
	Super::BeginPlay();

	if(Data->BoxClass.IsPending())
	{
		Data->BoxClass.LoadSynchronous();
	}

	float pitch = FMath::RandRange(-0.1f, 0.1f);
	float yaw = FMath::RandRange(-0.1f, 0.1f);
	float roll = FMath::RandRange(-0.1f, 0.1f);
	randomRotation = FRotator(pitch, yaw, roll) * Data->RotationSpeed;

	Refresh();
}

void AMengerSpongeFractal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RootComponent->AddWorldRotation(randomRotation);
}

void AMengerSpongeFractal::Generate()
{
	CurrentIteration++;

	if(CurrentIteration >= 4)
	{
		CurrentIteration = 0;
		Refresh();
		return;
	}

	TArray<AMengerSpongeFractalBox*> next;

	for(AMengerSpongeFractalBox* box : Sponge)
	{
		TArray<AMengerSpongeFractalBox*> newBoxes = box->Generate(this);
		next.Append(newBoxes);
		box->Destroy();
	}

	Sponge = next;

}

void AMengerSpongeFractal::Refresh()
{
	for(AMengerSpongeFractalBox* box : Sponge)
	{
		box->Destroy();
	}

	Sponge.Empty();

	FActorSpawnParameters param;
	param.Owner = this;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMengerSpongeFractalBox* box = GetWorld()->SpawnActor<AMengerSpongeFractalBox>(Data->BoxClass.Get(), FTransform(), param);
	box->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	Sponge.Add(box);
}
